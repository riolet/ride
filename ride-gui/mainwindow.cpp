#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(200, 200);
    container->setMaximumSize(200, 200);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("qrc:main.qml"));
    ui->verticalLayout->addWidget(container);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
