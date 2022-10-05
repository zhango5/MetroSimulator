#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_INCLUDE_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(FileParseWin)
QT_FORWARD_DECLARE_CLASS(ParseServiceWin)
QT_END_INCLUDE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTabWidgets();

private:
    QTabWidget*    _tab = nullptr;

    ParseServiceWin* _pParseSvrWin = nullptr;
    FileParseWin*  _pFileParseWin = nullptr;
};
#endif // MAINWINDOW_H
