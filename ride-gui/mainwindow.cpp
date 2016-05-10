#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*********************************************************************
 *   Small tutorial on how slots and signals work in Qt              *
 *********************************************************************
 * You can set up any Qt class (or custom Qt Object, it has to inherit
 * from a standard Qt Object) for throwing signals.
 *
 * Signals can carry parameters with them and you can set up any other
 * Qt class or Qt Object to catch that the sender's signal. connect is
 * a QtObject method for connecting signals to slots.
 *
 * connect(Qt_Object1,                           <-- Signal sender
 *         SIGNAL(signalMethod(int param_sent)), <-- Signal type
 *         Qt_Object2,                           <-- Signal catcher
 *         SLOT(slotMethod(int param_caught)));  <-- Signal handler
 *
 *********************************************************************
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupFileTree();
    setupScintilla();
    setupMenuActions();
    setupShortcuts(); //Not active atm
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScintilla()
{
    connect(ui->tabWidget_scintilla, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    ScintillaDoc* blank = new ScintillaDoc;
    textEditList.push_back(blank);
    cur_index = 0;

    cur_doc = textEditList[cur_index];

    ui->tabWidget_scintilla->removeTab(0);  // Remove the first unused tab
    ui->tabWidget_scintilla->removeTab(0);  // Remove the second unused tab

    ui->tabWidget_scintilla->addTab(blank->_editText, blank->_filename);
    connect(cur_doc, SIGNAL(textChanged()),
                this, SLOT(documentWasModified()));
}

void MainWindow::setupFileTree()
{
    model = new QFileSystemModel;
    QDir curDir = QDir::current();
    curDir.cdUp();

    model->setRootPath(curDir.path());

    tree = ui->tree_project_directory;
    tree->setModel(model);
    tree->setRootIndex(model->index(curDir.path()));
}

void MainWindow::setupShortcuts()
{
    // TODO: connect common keyboard shortcuts to various methods such as Ctrl+S to Save File
}

void MainWindow::setupMenuActions()
{
    connect(ui->actionNew_File, SIGNAL(triggered()), this, SLOT(on_button_new_file_clicked()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(on_button_open_clicked()));
    connect(ui->actionSave_File, SIGNAL(triggered()), this, SLOT(on_button_save_clicked()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionLicense, SIGNAL(triggered()), this, SLOT(displayLicense()));
    connect(ui->actionAbout_Rix, SIGNAL(triggered()), this, SLOT(displayAboutRix()));
    connect(ui->actionAbout_RIDE, SIGNAL(triggered()), this, SLOT(displayAboutRide()));
}

void MainWindow::saveAs()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString filepath = QFileDialog::getSaveFileName(this);

    if(!cur_doc->saveAs(filepath))
    {
        QMessageBox::warning(this, tr("Save File Error"),  tr("Cannot save the file %1\n%2.").arg(cur_doc->_filepath).arg(cur_doc->_errorString));
    }
    ui->tabWidget_scintilla->setTabText(cur_index, cur_doc->_filename);

    setDocumentModified(false);
    QApplication::restoreOverrideCursor();
}

void MainWindow::setDocumentModified(bool modified)
{
    QString tabtext = cur_doc->_filename;
    if(modified)
    {
        tabtext.prepend(QString("*"));
    }
    ui->tabWidget_scintilla->setTabText(cur_index, tabtext);
}

void MainWindow::displayAboutRix()
{
    // TODO: Display information about Rix
}

void MainWindow::displayAboutRide()
{
    // TODO: Display information about Ride
}

void MainWindow::displayLicense()
{
    QDir curDir = QDir::current();
    curDir.cdUp();
    QFile license(curDir.path() + QString("/LICENSE"));

    if(!license.open(QFile::ReadOnly))
    {
        std::cerr << "Couldn't open file" << std::endl;
        return;
    }

    QTextStream in(&license);
    QString body(in.readAll());
    QString title("GNU License");

    new AboutDialog(title, body);
}

void MainWindow::displayUnsavedChanges()
{
    /* UNTESTED
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    */
}

void MainWindow::loadFile(QString filepath)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(!cur_doc->loadFile(filepath))
    {
        QMessageBox::warning(this, tr("Load File Error"),  tr("Cannot read file %1\n%2.").arg(cur_doc->_filepath).arg(cur_doc->_errorString));
        return;
    }
    ui->tabWidget_scintilla->setTabText(cur_index, cur_doc->_filename);

    connect(cur_doc->_editText, SIGNAL(textChanged()), this, SLOT(documentWasModified()));
    statusBar()->showMessage(tr("File loaded"), 2000);
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_button_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::on_button_save_clicked()
{
    if(cur_doc->isBlank())
    {
        saveAs();
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    if(!cur_doc->saveFile())
    {
        QMessageBox::warning(this, tr("Save File Error"),  tr("Cannot save file %1\n%2.").arg(cur_doc->_filepath).arg(cur_doc->_errorString));
        statusBar()->showMessage(tr("Error saving the current file..."), 2000);
        return;
    }
    else
    {
        // TODO: set modified indicator off
        statusBar()->showMessage(tr("File saved"), 2000);
    }

    QApplication::restoreOverrideCursor();
    setDocumentModified(false);
}

// Remove the current document and recreate a blank one.
void MainWindow::on_button_new_file_clicked()
{
    if(!cur_doc->isBlank() && textEditList.size() > 0)
    {
        int last_ele = ui->tabWidget_scintilla->count() - 1;
        // Removes all old documents
        do
        {
            ui->tabWidget_scintilla->removeTab(last_ele);
            ScintillaDoc* old_doc = textEditList[last_ele];
            textEditList.pop_back();
            delete old_doc;

        } while(textEditList.size() > 0);

        ScintillaDoc* blank = new ScintillaDoc;
        textEditList.push_back(blank);

        cur_doc = textEditList[cur_index];

        ui->tabWidget_scintilla->addTab(blank->_editText, blank->_filename);
    }
    else
    {
        cur_doc->clearTextArea();
        setDocumentModified(false);
    }
}

void MainWindow::documentWasModified()
{
    setDocumentModified(true);
}

void MainWindow::tabChanged(int index)
{
    cur_index = index;
    cur_doc = textEditList[cur_index];
}

void MainWindow::on_button_zoom_in_clicked()
{
    cur_doc->zoom_in();
}

void MainWindow::on_button_zoom_out_clicked()
{
    cur_doc->zoom_out();
}

void MainWindow::on_button_saveall_clicked()
{
    //Dealing with one file only atm, redirect to save file.
    on_button_save_clicked();
}
