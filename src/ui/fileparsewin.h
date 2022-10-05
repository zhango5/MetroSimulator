#ifndef FILEPARSEWIN_H
#define FILEPARSEWIN_H

#include <QWidget>
#include "src/tools/fileparser.h"

QT_BEGIN_INCLUDE_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_END_INCLUDE_NAMESPACE

class FileParseWin : public QWidget
{
    Q_OBJECT
public:
    explicit FileParseWin(QWidget *parent = nullptr);
    ~FileParseWin();

private:
    QPushButton* _select = nullptr;
    QLineEdit*   _filePath = nullptr;
    QCheckBox*   _mode = nullptr;
    QLabel*      _class = nullptr;
    QLineEdit*   _class_text = nullptr;
    QLabel*      _type = nullptr;
    QLineEdit*   _type_text = nullptr;
    QPushButton* _export = nullptr;
    QTextEdit*   _result = nullptr;

    void init_widgets();
    void resolve_file_class(char fc);
    void resolve_file_type(char ft);
    void load_cfg_file();
    void save_cfg_file();

    FileParser _fParser;
    QString    _strOpenFolder;

signals:

private slots:
    void onFilePathClicked();
    void onExportJsonClicked();

};

#endif // FILEPARSEWIN_H
