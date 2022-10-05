#ifndef PARSESERVICEWIN_H
#define PARSESERVICEWIN_H

#include <QWidget>
#include <QTimer>
#include <QMap>
#include <QFile>
#include "src/tools/fileparser.h"
#include "qftp/qftp.h"

QT_BEGIN_INCLUDE_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QProgressBar)
QT_END_INCLUDE_NAMESPACE

typedef struct
{
    QString host;
    QString database;
    QString user;
    QString pwd;
    int     port;
} database_t;

typedef struct
{
    QString host;
    quint16 port;
    QString user;
    QString pwd;
    QString path;
} ftp_server_t;

typedef struct
{
    database_t db;
    int     nFetchInterval;
    ftp_server_t ftp;
    int     days;
    QString backup;
} file_parse_cfg_t;

class ParseServiceWin : public QWidget
{
public:
    explicit ParseServiceWin(QWidget* parent = nullptr);
    ~ParseServiceWin();

private:
    void init_widgets();
    void init_db_connect();
    void init_ftp_connect();
    void load_cfg_file();
    void parse_files();
    void save_json_file(const QString& filename, const rapidjson::StringBuffer& buffer);

    file_parse_cfg_t _cfg;
    FileParser _fParser;
    QFtp _ftp;
    QFtp* pFtp = nullptr;
    QTimer _fetchTimer;
    QStringList _files;
    QStringList _cache;
    QDate       _date;
    bool        _date_changed = false;
    QFtp::State _ftp_state = QFtp::State::Unconnected;

    QMap<int, QFile*> _download_list;

    QPushButton* _controller = nullptr;
    QProgressBar* _progressbar = nullptr;
};

#endif // PARSESERVICEWIN_H
