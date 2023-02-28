#include "parseservicewin.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QtEndian>
#include <QSettings>
#include <QTextCodec>
#include <QCoreApplication>
#include <QCheckBox>
#include <QStyle>
#include <QDebug>
#include <QtNetwork>

//#define __TEST_DEBUG__

#define CACHE_FOLDER "cache"
#define FOLDER_FMT   "yyyyMMdd"

ParseServiceWin::ParseServiceWin(QWidget* parent)
    : QWidget(parent)
{
    init_widgets();
    load_cfg_file();
    init_db_connect();
    init_ftp_connect();
    init_timer();
    clear_dirty_history();
    init_white_list();
}

ParseServiceWin::~ParseServiceWin()
{
    if (_fetchTimer.isActive())
    {
        _fetchTimer.stop();
    }

    if ( nullptr != pFtp )
    {
        disconnect( pFtp, nullptr, nullptr, nullptr );

        pFtp->close();
        pFtp->deleteLater();
    }
}

void ParseServiceWin::init_widgets()
{
    _controller = new QPushButton();
    _progressbar = new QProgressBar();

    _controller->setFixedSize(128, 128);
    _controller->setObjectName("ServerController");
    _controller->setProperty("state", "unchecked");

    _progressbar->setFixedSize(320, 30);
    _progressbar->setMinimum(0);
    _progressbar->setMaximum(100);
    _progressbar->setMaximum(50);
    _progressbar->setFormat("%v");
    _progressbar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QHBoxLayout* line1 = new QHBoxLayout();
    line1->addWidget(_controller);
    line1->setContentsMargins(0, 0, 0, 0);
    line1->setAlignment(Qt::AlignHCenter);
    QHBoxLayout* line2 = new QHBoxLayout();
    line2->addWidget(_progressbar);
    line2->setContentsMargins(0, 0, 0, 0);
    line2->setAlignment(Qt::AlignHCenter);
    QVBoxLayout* l = new QVBoxLayout();
    l->addLayout(line1);
    l->addLayout(line2);
    l->setContentsMargins(0, 0, 0, 0);
    l->setAlignment(Qt::AlignCenter);
    l->setSpacing(50);

    this->setLayout(l);

    connect(_controller, &QPushButton::pressed, this, [&]() {
        this->style()->unpolish(_controller);
        if ("checked" == _controller->property("state"))
        {
            _controller->setProperty("state", "unchecked");
            _fetchTimer.stop();
            _progressbar->setMaximum(100);
        }
        else
        {
            if (QFtp::State::LoggedIn == _ftp_state)
            {
                _controller->setProperty("state", "checked");
                _progressbar->setMaximum(0);
                if (!_fetchTimer.isActive())
                    _fetchTimer.start();
            }
            else
            {
                QMessageBox::warning(nullptr, "Warning", QString::fromLocal8Bit("FTP服务连接错误！"), QMessageBox::Ok);
                _controller->setProperty("state", "unchecked");
            }
        }
        this->style()->polish(_controller);
    });
}

void ParseServiceWin::init_db_connect()
{
    _fParser.OpenDB(_cfg.db.host, _cfg.db.database, _cfg.db.port, _cfg.db.user, _cfg.db.pwd);
}

void ParseServiceWin::init_ftp_connect()
{
    // connect FTP
    pFtp = new QFtp();
    QUrl url(_cfg.ftp.host);
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp"))
    {
        pFtp->connectToHost(_cfg.ftp.host, _cfg.ftp.port);
        pFtp->login(_cfg.ftp.user, _cfg.ftp.pwd);
    }
    else
    {
        pFtp->connectToHost(url.host(), url.port(_cfg.ftp.port));
        if (!url.userName().isEmpty())
            pFtp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
        else
            pFtp->login(_cfg.ftp.user, _cfg.ftp.pwd);
    }

    //if (!_cfg.ftp.path.isEmpty())
    //{
    //    pFtp->cd(_cfg.ftp.path);
    //}

    connect(pFtp, &QFtp::stateChanged, this, [&](int state ) {
        _ftp_state = static_cast<QFtp::State>( state );

        switch ( state )
        {
        case QFtp::Unconnected:
            qDebug() << "FTP state change unconnected.";
            break;
        case QFtp::Connected:
            qDebug() << "FTP state change connected.";
            break;
        case QFtp::HostLookup:
            qDebug() << "FTP state change hostlookup.";
            break;
        case QFtp::LoggedIn:
            qDebug() << "FTP state change logged in.";
            break;
        case QFtp::Closing:
            qDebug() << "FTP state change closing.";
            break;
        case QFtp::Connecting:
            qDebug() << "FTP state change connecting.";
            break;
        default:
            break;
        }
    });
    connect(pFtp, &QFtp::listInfo, this, [&](const QUrlInfo &info) {
        if (!info.isFile() || !info.isReadable())
        {
            // qDebug() << "list file error";
            return;
        }

        if (!_white_list.contains(info.name().left(2).toUpper()))
        {
            // not support
            _files.append(info.name());
            return;
        }

        if (!_files.contains(info.name())) {
            if (QFile::exists(QString("%1/%2/%3.json").arg(_backup.absolutePath()).arg(_date.toString(FOLDER_FMT)).arg(QFileInfo(info.name()).baseName())))
            {
                _files.append(info.name());
                return;
            }

            QFile* fp = new QFile(QString("%1/%2/%3").arg(QDir::currentPath(), CACHE_FOLDER, info.name()));
            if (fp->open(QIODevice::ReadWrite))
            {
                _download_list.insert(pFtp->get(info.name(), fp), fp);
                _cache.append(info.name());
            }
            else
            {
                qDebug() << "open file failed." << info.name();
            }
        }
    });
    connect(pFtp, &QFtp::commandFinished, this, [&](int id, bool error) {
        if (pFtp->currentCommand() == QFtp::Get)
        {
            QFile* fp = _download_list.value(id);
            QString fileName;
            if (nullptr != fp)
            {
                if (error)
                {
                    qDebug() << pFtp->errorString();
                    return;
                }

                fp->close();
                fileName = fp->fileName();
                delete fp;
                _download_list.remove(id);

                parse_file(fileName);
                QFile::remove(fileName);
            }
        }
        else if (pFtp->currentCommand() == QFtp::List)
        {
            //qDebug() << "list command finished....";
            _files.append(_cache);
            if (_date_changed) _files.clear();
        }
        else if (pFtp->currentCommand() == QFtp::ConnectToHost)
        {
            if (error)
            {
                qDebug() << "ftp connect to host error: " << pFtp->errorString();
            }
        }
        else if ( pFtp->currentCommand() == QFtp::Login )
        {
            if ( error )
            {
                qDebug() << "ftp login error: " << pFtp->errorString();
            }
        }
    });
    connect(pFtp, &QFtp::done, this, [&](bool error) {
        qDebug() << "ftp done!";

        if (error)
        {
            qDebug() << "ftp done but error: " << pFtp->errorString();
        }
    });
}

void ParseServiceWin::init_white_list()
{
    _white_list.append("UA");
    _white_list.append("UY");
    _white_list.append("UM");
    _white_list.append("UB");
    _white_list.append("UQ");
}

void ParseServiceWin::init_timer()
{
    // init timer
#ifdef __TEST_DEBUG__
    _fetchTimer.setInterval( 1000 );
    _fetchTimer.setSingleShot( true );
#else
    _fetchTimer.setInterval( _cfg.nFetchInterval * 1000 * 60 );
#endif
    connect( &_fetchTimer, &QTimer::timeout, this, [&] ()
    {
        if ( _date.isNull() )
        {
            _date = QDate::currentDate();
            _files.clear();
            QString path = QString( "%1%2" ).arg( _cfg.ftp.path ).arg( _date.toString( FOLDER_FMT ) );
            pFtp->list( path );
            pFtp->cd( path );
            // qDebug() << "cd " << path;
        }
        else
        {
            QDate today = QDate::currentDate();
            _date_changed = ( _date != today );

            QString path = QString( "%1%2" ).arg( _cfg.ftp.path ).arg( _date.toString( FOLDER_FMT ) );
            pFtp->list( path );
            pFtp->cd( path );
            // qDebug() << "change " << path;

            if ( _date_changed )
                _date = today;
        }
    } );

    _resetTimer.setInterval( 60 * 60 * 1000 ); /// 1 hour
    connect( &_resetTimer, &QTimer::timeout, this, [&] () {
        if ( nullptr != pFtp )
        {
            // reset ftp
            qDebug() << "reset ftp connect !!!";

            pFtp->abort();
            pFtp->close();
            pFtp->deleteLater();
            pFtp = nullptr;
        }

        init_ftp_connect();
        _fetchTimer.start();
    } );

    _resetTimer.start();
}

void ParseServiceWin::load_cfg_file()
{
    QSettings cfg("./parsewincfg.ini", QSettings::IniFormat);
    cfg.setIniCodec(QTextCodec::codecForName("GBK"));

    cfg.beginGroup("database");
    _cfg.db.host = cfg.value("hostname").toString();
    _cfg.db.database = cfg.value("database").toString();
    _cfg.db.user = cfg.value("username").toString();
    _cfg.db.pwd = cfg.value("password").toString();
    _cfg.db.port = cfg.value("port").toInt();
    cfg.endGroup();

    cfg.beginGroup("config");
    _cfg.nFetchInterval = cfg.value("interval").toInt();
    cfg.endGroup();

    cfg.beginGroup("ftp");
    _cfg.ftp.host = cfg.value("host").toString();
    _cfg.ftp.port = cfg.value("port").toInt();
    _cfg.ftp.user = cfg.value("username").toString();
    _cfg.ftp.pwd = cfg.value("password").toString();
    _cfg.ftp.path = cfg.value("path").toString();
    cfg.endGroup();

    cfg.beginGroup("history");
    _cfg.days = cfg.value("days").toInt();
    _cfg.backup = cfg.value("backup").toString();
    cfg.endGroup();

    _backup.setPath(_cfg.backup);
    if (!_backup.exists())
    {
        if (!_backup.mkpath(_cfg.backup))
        {
            qDebug() << "make back up folder failed!" << _cfg.backup;
        }
    }

    QDir dir;
    if (!dir.exists(CACHE_FOLDER))
    {
        dir.mkdir(CACHE_FOLDER);
    }
}

void ParseServiceWin::parse_file(const QString& fileName)
{
    QFile fp(fileName);

    if (fp.open(QIODevice::ReadOnly))
    {
        QByteArray ba = fp.readAll();
        fp.close();
        rapidjson::StringBuffer buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);

        switch (qFromBigEndian<uint32_t>(ba.left(4).data()))
        {
        case 0x01:
            _fParser.YiPiaoTongTradeFile(writer, ba);
            break;

        case 0x02:
            _fParser.YiKaTongTradeFile(writer, ba);
            break;

        case 0x03:
            _fParser.PhoneTicketTradeFile(writer, ba);
            break;

        case 0x04:
            _fParser.BankCardTradeFile(writer, ba);
            break;

        case 0x70:
            _fParser.QRCodeTradeFile(writer, ba);
            break;
        }

        save_json_file(fileName, buf);
    }
    else
    {
        qDebug() << "file open failed. file name: " << fileName;
    }
}

void ParseServiceWin::save_json_file(const QString& filename, const rapidjson::StringBuffer& buffer)
{
    QFileInfo fi(filename);
    QString date = fi.fileName().mid(12, 8);
    QDate dt = QDate::fromString(date, FOLDER_FMT);
    if (!dt.isValid())
    {
        qDebug() << "file name error. parse date error. " << filename;
    }

    QDir dir(_cfg.backup);
    if (!dir.exists())
    {
        if (!dir.mkpath(_cfg.backup))
        {
            qDebug() << "make back up path error";
            return;
        }
    }

    if (!dir.exists(dir.absolutePath() + "/" + date))
    {
        if (!dir.mkpath(dir.absolutePath() + "/" + date))
        {
            qDebug() << "make json folder path error";
            return;
        }
    }

    dir.cd(date);

    QString filepath = QString("%1/%2.json").arg(dir.absolutePath()).arg(fi.baseName());

    QFile fp(filepath);

    if (fp.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        fp.write(buffer.GetString());
        fp.close();
    }
    else
    {
        qDebug() << "save to json open file error! " << filepath;
    }
}

void ParseServiceWin::clear_dirty_history()
{
    QDir dir(_cfg.backup);
    if (!dir.exists())
    {
        qDebug() << "back up folder is not exist!";
        return;
    }

    QStringList folders = dir.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QDate dt;
    QDate date = QDate::currentDate();

    foreach (QString folder, folders)
    {
        dt = QDate::fromString(folder, FOLDER_FMT);

        if (dt.daysTo(date) > _cfg.days)
        {
            dir.cd(folder);
            if (!dir.removeRecursively())
            {
                qDebug() << "remove folder failed." << folder;
            }
            dir.cdUp();
        }
    }
}

