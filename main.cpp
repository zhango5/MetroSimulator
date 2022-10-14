#include "src/ui/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>

//#define __LOG_PLUS__
#define LOGFILE   "./log/log.txt"

void logMessageHandler(QtMsgType type, const QMessageLogContext& Context, const QString &sMsg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(logMessageHandler);
    QFileInfo file(LOGFILE);
    QDir dir;
    dir.mkdir(file.absolutePath());
    if (file.size() > 10 * 1024 * 1024)    // 10MB
    {
        QFile::remove(file.absoluteFilePath());
    }

    qDebug("application start ...");

    MainWindow w;
    w.show();
    a.exec();

    qDebug("application quit ...");

    return 0;
}

/*****************************************************************************
 函 数 名  : logMessageHandler
 功能描述  : 调试信息回调函数
 输入参数  : QtMsgType type
             const QMessageLogContext& Context
             const QString &sMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月15日
    作    者   : zhangxiang
    修改内容   : 新生成函数

*****************************************************************************/
void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    if (msg.contains("deprecated"))
    {
        // 屏蔽Qt输出告警
        return;
    }
    Q_UNUSED(context);
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtInfoMsg:
        text = QString("Info:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
        break;
    }

#ifdef __LOG_PLUS__
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
#else
    QString context_info;
#endif
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(current_date).arg(context_info).arg(msg);

    QFile file(LOGFILE);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
}

