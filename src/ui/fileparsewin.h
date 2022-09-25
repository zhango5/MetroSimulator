#ifndef FILEPARSEWIN_H
#define FILEPARSEWIN_H

#include <QWidget>

QT_BEGIN_INCLUDE_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_END_INCLUDE_NAMESPACE

typedef struct
{
    QString strOpenPath;
    int     nFetchInterval;
} file_parse_cfg_t;

class FileParseWin : public QWidget
{
    Q_OBJECT
public:
    explicit FileParseWin(QWidget *parent = nullptr);

    void init_widgets();

private:
    QPushButton* _select = nullptr;
    QLineEdit*   _filePath = nullptr;
    QLabel*      _class = nullptr;
    QLineEdit*   _class_text = nullptr;
    QLabel*      _type = nullptr;
    QLineEdit*   _type_text = nullptr;
    QPushButton* _export = nullptr;
    QTextEdit*   _result = nullptr;

    void resolveFileClass(char fc);
    void resolveFileType(char ft);
    void loadCfgFile();
    void saveCfgFile();

    file_parse_cfg_t _cfg;

signals:

private slots:
    void onFilePathClicked();
    void onExportJsonClicked();

};

#endif // FILEPARSEWIN_H
