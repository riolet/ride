#include <QDebug>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupFileTree();
    setupScintilla();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScintilla()
{
    ScintillaDoc blank;
    textEditList.push_back(blank);
    cur_index = 0;

    ui->tabWidget_scintilla->removeTab(0);  // Remove the first unused tab
    ui->tabWidget_scintilla->removeTab(0);  // Remove the second unused tab

    ui->tabWidget_scintilla->addTab(blank._doc, blank._name);
}

void MainWindow::setupFileTree()
{
    QFileSystemModel *model = new QFileSystemModel;
    QDir curDir = QDir::current();
    curDir.cdUp();

    model->setRootPath(curDir.path());

    tree = ui->tree_project_directory;
    tree->setModel(model);
    tree->setRootIndex(model->index(curDir.path()));
}
