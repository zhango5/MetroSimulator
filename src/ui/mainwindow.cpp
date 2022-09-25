#include "mainwindow.h"
#include "fileparsewin.h"
#include <QHBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(800, 600);

    this->setCentralWidget(new QWidget());

    _tab = new QTabWidget();

    QHBoxLayout* l = new QHBoxLayout();
    l->addWidget(_tab);
    l->setContentsMargins(0, 0, 0, 0);
    this->centralWidget()->setLayout(l);

    QFile fi("://style/stylesheet.qss");
    if (fi.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(fi.readAll());
        fi.close();
    }

    initTabWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initTabWidgets()
{
    _pFileParseWin = new FileParseWin();

    _tab->addTab(_pFileParseWin, QString::fromLocal8Bit("文件解析"));
}

