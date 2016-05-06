#include <QDebug>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setupFileTree();
    setupScintilla();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScintilla()
{
    textEdit = new QsciScintilla;
    ui->horizontalLayout_scintilla->addWidget(textEdit);
}

void MainWindow::setupFileTree()
{
    QFileSystemModel *model = new QFileSystemModel;
    QDir curDir = QDir::current();
    curDir.cdUp();

    tree = ui->tree_project_directory;
    tree->setRootIndex(model->setRootPath(curDir.path()));

    /*QFileSystemModel *model = new QFileSystemModel;
    model->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    QDir curDir = QDir::current();
    curDir.cdUp();

    tree = ui->tree_project_directory;
    tree->setRootIndex(model->setRootPath(curDir.path()));*/
}
