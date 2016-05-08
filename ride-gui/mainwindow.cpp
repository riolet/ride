#include <QDebug>
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

    cur_doc = &textEditList[cur_index];

    ui->tabWidget_scintilla->removeTab(0);  // Remove the first unused tab
    ui->tabWidget_scintilla->removeTab(0);  // Remove the second unused tab

    ui->tabWidget_scintilla->addTab(blank._editText, blank._filename);
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

void MainWindow::loadFile(QString filepath)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(!cur_doc->loadFile(filepath))
    {
        QMessageBox::warning(this, tr("ERROR"),  tr("Cannot read file %1.").arg(filepath).arg(cur_doc->_errorString));
        return;
    }

    QApplication::restoreOverrideCursor();
    ui->tabWidget_scintilla->setTabText(cur_index, cur_doc->_filename);

    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::on_button_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}
