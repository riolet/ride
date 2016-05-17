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
    setupTheme();
    setupCompiler();
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
    ui->actionGo_to_line->setShortcut(tr("Ctrl+G"));
    /*
    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()))*/

    // TODO: connect common keyboard shortcuts to various methods such as Ctrl+S to Save File
}

void MainWindow::setupMenuActions()
{   
    connect(ui->actionNew_File,     SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen,         SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave_File,    SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSave_As,      SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionGo_to_line,   SIGNAL(triggered()), this, SLOT(gotoLine()));
    connect(ui->actionLicense,      SIGNAL(triggered()), this, SLOT(displayLicense()));
    connect(ui->actionAbout_Rix,    SIGNAL(triggered()), this, SLOT(displayAboutRix()));
    connect(ui->actionAbout_RIDE,   SIGNAL(triggered()), this, SLOT(displayAboutRide()));
    connect(ui->actionExit,         SIGNAL(triggered()), this, SLOT(sendCloseEvent()));
}

bool MainWindow::saveAs()
{
    bool isSuccessful = false;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString filepath = QFileDialog::getSaveFileName(this);

    if(!cur_doc->saveAs(filepath))
    {
        isSuccessful = false;
    }
    else
    {
        ui->tabWidget_scintilla->setTabText(cur_index, cur_doc->_filename);
        setDocumentModified(false);
        isSuccessful = true;
    }

    QApplication::restoreOverrideCursor();

    return isSuccessful;
}

bool MainWindow::save()
{
    bool isSuccessful = false;
    if(cur_doc->isBlank())
    {
        return saveAs();
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    if(!cur_doc->saveFile())
    {
        isSuccessful = false;
    }
    else
    {
        isSuccessful = true;
        statusBar()->showMessage(tr("File saved"), 2000);
        setDocumentModified(false);
    }

    QApplication::restoreOverrideCursor();
    return isSuccessful;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::newFile()
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
        bool clearDoc = false;
        // Force user to make a decision on keeping or discarding changes.

        clearDoc = displayUnsavedChanges();

        if(clearDoc)
        {
            // Simply just clean up the current blank document.
            cur_doc->clearTextArea();
            setDocumentModified(false);
        }
    }
}

void MainWindow::gotoLine()
{
    QString tacos = cur_doc->getAllText();
    std::cerr << tacos.toStdString() << std::endl;
    /*bool ok;
    int max = cur_doc->getTotalLines();
    int line = QInputDialog::getInt(this, tr("Go to"), tr("line:"), 1, 1, max, 1, &ok);

    if(ok)
    {
        cur_doc->gotoLine(line);
    }*/
}

void MainWindow::runCompiler()
{
    clearCompilerMessages();
    if(cur_doc->isBlank())
    {
        compiler->compileRixFile();
    }
    else
    {
        compiler->compileRixFile(cur_doc);
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool quit = true;

    if(cur_doc->isModified())
        quit = displayUnsavedChanges();

    if(quit)
    {
        QMainWindow::closeEvent(event);
        close();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::sendCloseEvent()
{
    closeEvent(new QCloseEvent());
}

void MainWindow::readCompilerOutputLine(const QString& line)
{
    ui->text_output->appendPlainText(line);
}

void MainWindow::readCompilerErrorLine(const QString &err)
{
    ui->text_issues->appendPlainText(err);
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

void MainWindow::setupCompiler()
{
    clearCompilerMessages();
    compiler = new CompilerHandler(this);
    connect(compiler, SIGNAL(compilerOutput(QString)), this, SLOT(readCompilerOutputLine(QString)));
    connect(compiler, SIGNAL(compilerError(QString)),  this, SLOT(readCompilerErrorLine(QString)));
}

void MainWindow::setupTheme()
{
    themer = new ThemeHandler();
}

void MainWindow::clearCompilerMessages()
{
    ui->text_issues->setPlainText("");
    ui->text_output->setPlainText("");
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

bool MainWindow::displayUnsavedChanges()
{
    bool quit = true;
    bool flag = false;

    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    /*
     * Continous loop to force the user make a decision
     * between saving / discard / cancel saved changes.
     */
    do{
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
            flag = save();
            quit = true;
            statusBar()->showMessage(tr("Error saving the current file..."), 2000);
            break;
        case QMessageBox::Discard:
            flag = true;
            quit = true;
            break;
        case QMessageBox::Cancel:
            flag = true;
            quit = false;
            break;
        }
    } while(!flag);

    return quit;
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

void MainWindow::documentWasModified()
{
    setDocumentModified(true);
}

void MainWindow::tabChanged(int index)
{
    cur_index = index;
    cur_doc = textEditList[cur_index];
}

void MainWindow::on_button_open_clicked()
{
    open();
}

void MainWindow::on_button_save_clicked()
{
    save();
}

void MainWindow::on_button_new_file_clicked()
{
    newFile();
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
    save();
}

void MainWindow::on_button_run_clicked()
{
    runCompiler();
}
