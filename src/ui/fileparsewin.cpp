#include "fileparsewin.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFile>
#include <QtEndian>
#include <QSettings>
#include <QTextCodec>
#include <QCoreApplication>
#include <QCheckBox>
#include <QDebug>
#include <exception>

FileParseWin::FileParseWin(QWidget *parent)
    : QWidget(parent)
{
    init_widgets();
    loadCfgFile();

    if (_cfg.strOpenPath.isEmpty())
    {
        _cfg.strOpenPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }
}

void FileParseWin::init_widgets()
{
    _select = new QPushButton(QString::fromLocal8Bit("选择文件"));
    _filePath = new QLineEdit();
    _mode = new QCheckBox();
    _class = new QLabel(QString::fromLocal8Bit("文件类别"));
    _class_text = new QLineEdit();
    _type = new QLabel(QString::fromLocal8Bit("文件类型"));
    _type_text = new QLineEdit();
    _export = new QPushButton(QString::fromLocal8Bit("导出"));
    _result = new QTextEdit();

    _select->setFixedSize(80, 25);
    _export->setFixedSize(80, 25);
    _filePath->setFixedHeight(25);
    _filePath->setReadOnly(true);
    _result->setReadOnly(true);

    connect(_select, &QPushButton::clicked, this, &FileParseWin::onFilePathClicked);
    connect(_export, &QPushButton::clicked, this, &FileParseWin::onExportJsonClicked);

    QVBoxLayout* l = new QVBoxLayout();

    QHBoxLayout* filepath = new QHBoxLayout();
    QHBoxLayout* fileinfo = new QHBoxLayout();

    filepath->addWidget(_select);
    filepath->addWidget(_filePath);
    filepath->addWidget(_mode);
    filepath->setContentsMargins(0, 0, 0, 0);
    filepath->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    filepath->setSpacing(10);

    fileinfo->addWidget(_class);
    fileinfo->addWidget(_class_text);
    fileinfo->addSpacing(30);
    fileinfo->addWidget(_type);
    fileinfo->addWidget(_type_text);
    fileinfo->addSpacing(50);
    fileinfo->addWidget(_export);
    fileinfo->setContentsMargins(0, 0, 0, 0);
    fileinfo->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    fileinfo->setSpacing(10);

    l->addLayout(filepath);
    l->addLayout(fileinfo);
    l->addWidget(_result);
    l->setContentsMargins(10, 10, 10, 10);
    l->setAlignment(Qt::AlignCenter);
    l->setSpacing(5);

    this->setLayout(l);
}

void FileParseWin::resolveFileClass(char fc)
{
    switch (fc) {
    case 'U':
    case 'u':
        _class_text->setText(QString::fromLocal8Bit("交易数据"));
        break;
    default:
        break;
    }
}

void FileParseWin::resolveFileType(char ft)
{
    switch (ft) {
    case 'A':
    case 'a':
        _type_text->setText(QString::fromLocal8Bit("一票通交易文件"));
        break;
    case 'Y':
    case 'y':
        _type_text->setText(QString::fromLocal8Bit("一卡通交易文件"));
        break;
    case 'M':
    case 'm':
        _type_text->setText(QString::fromLocal8Bit("手机票交易文件"));
        break;
    case 'B':
    case 'b':
        _type_text->setText(QString::fromLocal8Bit("银行卡交易文件"));
        break;
    case 'Q':
    case 'q':
        _type_text->setText(QString::fromLocal8Bit("二维码交易文件"));
        break;
    default:
        break;
    }
}

void FileParseWin::loadCfgFile()
{
    QSettings cfg("./parsewincfg.ini", QSettings::IniFormat);
    cfg.setIniCodec(QTextCodec::codecForName("GBK"));

    cfg.beginGroup("folder");
    _cfg.strOpenPath = cfg.value("path").toString();
    cfg.endGroup();

    cfg.beginGroup("config");
    _cfg.nFetchInterval = cfg.value("interval").toInt();
    cfg.endGroup();
}

void FileParseWin::saveCfgFile()
{
    QSettings cfg("./parsewincfg.ini", QSettings::IniFormat);
    cfg.setIniCodec(QTextCodec::codecForName("GBK"));

    cfg.beginGroup("folder");
    cfg.setValue("path", _cfg.strOpenPath);
    cfg.endGroup();

    cfg.beginGroup("config");
    cfg.setValue("interval", _cfg.nFetchInterval);
    cfg.endGroup();
}

void FileParseWin::onFilePathClicked()
{
    if (_mode->isChecked())
    {
        QString folder = QFileDialog::getExistingDirectory(nullptr
                                                        , QString::fromLocal8Bit("选择目录")
                                                        , _cfg.strOpenPath
                                                        , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//        QString folder = "D:/20220904";
        if (folder.isEmpty())
        {
            return;
        }

        QDir dir(folder);
        QStringList files = dir.entryList(QDir::Files);

        for (int i = 0; i < files.size(); ++i)
        {
            QString name = files[i];

            QFile fp(folder + "/" + name);
            if (!fp.open(QIODevice::ReadOnly))
            {
                QMessageBox::warning(nullptr, "Warning", "file open failed!", QMessageBox::Ok);
                return;
            }

            QByteArray ba = fp.readAll();
            fp.close();

            _fParser.filePath = fp.fileName();

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

            _result->setText(QString("%1/%2").arg(i + 1).arg(files.size()));

            QCoreApplication::processEvents();
        }

        _cfg.strOpenPath = folder;
        saveCfgFile();

//        _fParser.output();
    }
    else
    {
        QString filePath = QFileDialog::getOpenFileName(nullptr
                                                        , QString::fromLocal8Bit("选择文件")
                                                        , _cfg.strOpenPath // QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                                                        , "*.*");

    //    QString filePath = "D:/20220829/UY01990101052022082906370901.01283A";

        if (filePath.isEmpty())
        {
            return;
        }

        QFileInfo fi(filePath);

        if (fi.completeBaseName().length() < 26
            || fi.suffix().length() != 6)
        {
            QMessageBox::warning(nullptr, "Warning", "The file doesn't match!", QMessageBox::Ok);
            return;
        }

        if (0 != _cfg.strOpenPath.compare(fi.absoluteDir().absolutePath(), Qt::CaseSensitive))
        {
            _cfg.strOpenPath = fi.absoluteDir().absolutePath();
            saveCfgFile();
        }

        _filePath->setText(filePath);

        QString fileName = fi.completeBaseName();

        resolveFileClass(fileName[0].toLatin1());
        resolveFileType(fileName[1].toLatin1());

        QFile fp(filePath);
        if (!fp.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(nullptr, "Warning", "file open failed!", QMessageBox::Ok);
            return;
        }

        QByteArray ba = fp.readAll();
        fp.close();

        rapidjson::StringBuffer buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);

        try
        {
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
        } catch (std::exception &e) {
            qDebug() << "exception: " << e.what() << endl;
            qDebug() << "exception file:" << filePath;
        }

        _result->setText(buf.GetString());
    }
}

void FileParseWin::onExportJsonClicked()
{
    QString json = _result->toPlainText();
    if (json.isEmpty()) return;

    QString filePath = QFileDialog::getSaveFileName(nullptr
                                                    , QString::fromLocal8Bit("保存文件")
                                                    , QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                                                    , "*.json");
    if (filePath.isEmpty()) return;

    QFile fp(filePath);
    if (!fp.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::warning(nullptr, "Warning", "create file failed!", QMessageBox::Ok);
        return;
    }

    fp.write(json.toUtf8());
    fp.close();
}
