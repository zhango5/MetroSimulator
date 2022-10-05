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

#define CACHE_FOLDER "cache"

ParseServiceWin::ParseServiceWin(QWidget* parent)
    : QWidget(parent)
{
    init_widgets();
    load_cfg_file();
    init_db_connect();
    init_ftp_connect();
}

ParseServiceWin::~ParseServiceWin()
{
    _ftp.close();
}

void ParseServiceWin::init_widgets()
{
    _controller = new QPushButton();
    _progressbar = new QProgressBar();

    _controller->setFixedSize(128, 128);
    _controller->setObjectName("ServerController");
    _controller->setProperty("state", "unchecked");
//    _controller->setCheckable(true);
//    _controller->setText(QString::fromLocal8Bit("启动服务"));

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
        }
        else
        {
            if (QFtp::State::LoggedIn == _ftp_state)
            {
                _controller->setProperty("state", "checked");
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
    QUrl url(_cfg.ftp.host);
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp"))
    {
        _ftp.connectToHost(_cfg.ftp.host, _cfg.ftp.port);
        _ftp.login(_cfg.ftp.user, _cfg.ftp.pwd);
    }
    else
    {
        _ftp.connectToHost(url.host(), url.port(_cfg.ftp.port));
        if (!url.userName().isEmpty())
            _ftp.login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
        else
            _ftp.login(_cfg.ftp.user, _cfg.ftp.pwd);
    }

    _ftp.cd(_cfg.ftp.path);

    connect(&_ftp, &QFtp::stateChanged, this, [&](int st) {
        _ftp_state = static_cast<QFtp::State>(st);
    });
    connect(&_ftp, &QFtp::listInfo, this, [&](const QUrlInfo &info) {
        if (!info.isFile() || !info.isReadable())
        {
            return;
        }

        if (!_files.contains(info.name())) {
            QFile* fp = new QFile(QString("%1/%2/%3").arg(QDir::currentPath(), CACHE_FOLDER, info.name()));
            if (fp->open(QIODevice::ReadWrite))
            {
                _download_list.insert(_ftp.get(info.name(), fp), fp);
                _cache.append(info.name());
            }
            else
            {
                qDebug() << "open file failed.";
            }
        }
    });
    connect(&_ftp, &QFtp::commandFinished, this, [&](int id, bool error) {
        if (_ftp.currentCommand() == QFtp::Get)
        {
            QFile* fp = _download_list.value(id);
            if (nullptr != fp)
            {
                if (error)
                {
                    qDebug() << _ftp.errorString();
                    return;
                }

                QByteArray ba = fp->readAll();
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

                save_json_file(fp->fileName(), buf);
                fp->close();
                delete fp;
                _download_list.remove(id);
            }
        }
        else if (_ftp.currentCommand() == QFtp::List)
        {
            qDebug() << "list command finished....";
            _files.append(_cache);
            if (_date_changed) _files.clear();
        }
        else if (_ftp.currentCommand() == QFtp::ConnectToHost)
        {
            if (error)
            {
                qDebug() << "ftp error: " << _ftp.errorString();
            }
        }
    });

    // init timer
    _fetchTimer.setInterval(_cfg.nFetchInterval);
    _fetchTimer.setSingleShot(true);
    connect(&_fetchTimer, &QTimer::timeout, this, [&]() {
        if (_date.isNull())
        {
            _date = QDate::currentDate();
            _files.clear();
            QString path = QString("%1%2").arg(_cfg.ftp.path).arg(_date.toString("yyyyMMdd"));
            _ftp.list(path);
            _ftp.cd(path);
        }
        else
        {
            QDate today = QDate::currentDate();
            _date_changed = (_date != today);

            QString path = QString("%1%2").arg(_cfg.ftp.path).arg(_date.toString("yyyyMMdd"));
            _ftp.list(path);
            _ftp.cd(path);

            if (_date_changed)
                _date = today;
        }

    });
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

    QDir dir;
    if (!dir.exists(_cfg.backup))
    {
        if (!dir.mkpath(_cfg.backup))
        {
            qDebug() << "make path failed!" << _cfg.backup;
        }
    }

    if (!dir.exists(CACHE_FOLDER))
    {
        dir.mkdir(CACHE_FOLDER);
    }
}

void ParseServiceWin::parse_files()
{
    for (int i = 0; i < _cache.size(); ++i)
    {
        QFile fp(_cfg.ftp.path + _cache.at(i));
        if (!fp.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(nullptr, "Warning", "file open failed!", QMessageBox::Ok);
            return;
        }

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

//        save_json_file(buf);

        QCoreApplication::processEvents();
    }
}

void ParseServiceWin::save_json_file(const QString& filename, const rapidjson::StringBuffer& buffer)
{
    QString date = filename.mid(12, 8);
    QDir dir;
    if (!dir.exists(_cfg.backup + date))
    {
        dir.mkdir(_cfg.backup + date);
    }

    QFile fp(dir.absolutePath() + "/" + filename);

    if (fp.open(QIODevice::WriteOnly))
    {
        fp.write(buffer.GetString());
        fp.close();
    }
}

