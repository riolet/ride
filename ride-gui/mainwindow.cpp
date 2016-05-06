#include <QDebug>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createIcons();
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

void MainWindow::createIcons()
{
    //  Save Button
    QPixmap pix(":/icons/filesave.png");
    QIcon icon(pix);
    ui->button_save->setIcon(icon);
    ui->button_save->setIconSize(QSize(32,32));
}
