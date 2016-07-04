/*===============================================================================
SOURCE FILE:    mainwindow.cpp
                    Singleton class that contains a compiler, a lexer,
                    the components for rix compilation and the scintilla edit
                    text surface.

PROGRAM:        Ride

FUNCTIONS:      void on_button_open_clicked();
                void on_button_save_clicked();
                void on_button_new_file_clicked();
                void on_button_zoom_in_clicked();
                void on_button_zoom_out_clicked();
                void on_button_saveall_clicked();
                void on_button_run_clicked();
                
                void displayAboutRix();
                void displayAboutRide();
                void displayErrorMessage(const QString &title, const QString &msg);
                void displayLicense();
                bool displaySaveOrIgnoreChanges();
                bool displayUnsavedChanges();
                
                void setupCompiler();
                void setupFileTree();
                void setupMenuActions();
                void setupScintilla();
                void setupShortcuts(); // Not done yet.
                void setupTheme();
                
                bool saveAs();
                bool save();
                void open();
                void newFile();
                void gotoLine();
                bool runCompiler();
                void loadFile(QString filepath);
                void undo();
                void redo();
                
                void readCompilerOutputLine(const QString& line);
                void readCompilerErrorLine(const QString& err);
                
                void closeEvent(QCloseEvent *event);
                void sendCloseEvent();
                
                void setDocumentModified(bool modified);
                void tabChanged(int index);
                void documentWasModified();
                
                void clearCompilerMessages();

PROGRAMMER(S):  Tyler Trepanier-Bracken, Micah Willems

NOTES:
This source file defines all of the functions that are declared inside of the
compilerhandler.h file. This class runs the "rix" shell script and sends all
compilation messages to the mainwindow. This is done via signals which are
caught by the mainwindow slot. It also preforms other standard text editor
functions but it is mainly focused on how Rix operates.
===============================================================================*/

#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

/***********************************************************************
 *   Small tutorial on how slots and signals work in Qt                *
 ***********************************************************************
 * You can set up any Qt class (or custom Qt Object, it has to inherit *
 * from a standard Qt Object) for throwing signals.                    *
 *                                                                     *
 * Signals can carry parameters with them and you can set up any other *
 * Qt class or Qt Object to catch that the sender's signal. connect is *
 * a QtObject method for connecting signals to slots.                  *
 *                                                                     *
 * connect(Qt_Object1,                           <-- Signal sender     *
 *         SIGNAL(signalMethod(int param_sent)), <-- Signal type       *
 *         Qt_Object2,                           <-- Signal catcher    *
 *         SLOT(slotMethod(int param_caught)));  <-- Signal handler    *
 *                                                                     *
 **********************************************************************/

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
    setupShortcuts();
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
    connect(cur_doc, SIGNAL(textChanged()), this, SLOT(documentWasModified()));
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
    tree->hideColumn(1);
    tree->hideColumn(2);
    tree->hideColumn(3);
}

void MainWindow::setupShortcuts()
{
    ui->actionGo_to_line->setShortcut(Qt::CTRL | Qt::Key_G);
    ui->actionNew_File->setShortcut(Qt::CTRL | Qt::Key_N);
    ui->actionOpen->setShortcut(Qt::CTRL | Qt::Key_O);
    ui->actionSave_File->setShortcut(Qt::CTRL | Qt::Key_S);
    ui->actionSave_All->setShortcut(Qt::Key_Shift | Qt::CTRL | Qt::Key_S);
    ui->actionZoom_In->setShortcut(Qt::Key_Plus| Qt::CTRL);
    ui->actionZoom_Out->setShortcut(Qt::CTRL | Qt::Key_Minus);
    ui->actionUndo->setShortcut(Qt::CTRL | Qt::Key_Z);
    ui->actionRedo->setShortcut(Qt::CTRL | Qt::Key_Y);
    ui->actionLicense->setShortcut(Qt::Key_F1);
    ui->actionAbout_RIDE->setShortcut(Qt::Key_F2);
    ui->actionAbout_Rix->setShortcut(Qt::Key_F3);
    ui->actionCopy->setShortcut(Qt::CTRL | Qt::Key_C);
    ui->actionCut->setShortcut(Qt::CTRL | Qt::Key_X);
    ui->actionPaste->setShortcut(Qt::CTRL | Qt::Key_V);
    ui->actionRun->setShortcut(Qt::CTRL | Qt::Key_R);
}

void MainWindow::setupMenuActions()
{   
    connect(ui->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionNew_Project,  SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->actionNew_File,     SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen,         SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave_File,    SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSave_As,      SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionGo_to_line,   SIGNAL(triggered()), this, SLOT(gotoLine()));
    connect(ui->actionLicense,      SIGNAL(triggered()), this, SLOT(displayLicense()));
    connect(ui->actionAbout_Rix,    SIGNAL(triggered()), this, SLOT(displayAboutRix()));
    connect(ui->actionAbout_RIDE,   SIGNAL(triggered()), this, SLOT(displayAboutRide()));
    connect(ui->actionExit,         SIGNAL(triggered()), this, SLOT(sendCloseEvent()));
    connect(ui->actionUndo,         SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionRedo,         SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->actionCut,          SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->actionCopy,         SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionPaste,        SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->actionRun,          SIGNAL(triggered()), this, SLOT(runCompiler()));
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

void MainWindow::undo()
{
    cur_doc->_editText->undo();
}

void MainWindow::redo()
{
    cur_doc->_editText->redo();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::openProject()
{
    QString selfilter = tr("Project files (*.prox)");
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Project",
            "/home",
            tr("Project files (*.prox);;RIX (*.rit *.rix);;All files (*.*)" ),
            &selfilter
    );

    project = new ProjectHandler(&filename);

}

void MainWindow::newProject()
{

}

void MainWindow::newFile()
{
    bool flag = false;

    // Prompt for user action
    if(cur_doc->isModified())
    {
        flag = displayUnsavedChanges();

        if(!flag) // User decided to cancel this operation.
            return;
    }
    else if(!cur_doc->isBlank() && !cur_doc->isModified())
    {
        QString title("Close the current file...");
        QString msg("Are you sure you want to close the current file?");
        flag = displayAreYouSure(title, msg);

        if(!flag) // User decided to cancel this operation.
            return;
    }

    // Accomplish the task of clearing the scintilla text field.
    if(!cur_doc->isBlank() && textEditList.size() > 0)
    {
        // Removes all old documents
        int last_ele = ui->tabWidget_scintilla->count() - 1;
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
        // Simply just clean up the current blank document.
        cur_doc->clearTextArea();
        setDocumentModified(false);
    }
}

void MainWindow::gotoLine()
{
    bool ok; // Boolean that checks to see if the user clicked ok.
    int max = cur_doc->getTotalLines();
    int line = QInputDialog::getInt(this, tr("Go to"), tr("line:"), 1, 1, max, 1, &ok);

    if(ok)
    {
        cur_doc->gotoLine(line);
    }
}

void MainWindow::copy()
{
    cur_doc->copy();
}

void MainWindow::cut()
{
    cur_doc->cut();
}

void MainWindow::paste()
{
    cur_doc->paste();
}

bool MainWindow::runCompiler()
{
    clearCompilerMessages();

    if(cur_doc->isBlank())
    {
        displayErrorMessage(QString("Compiler"), QString("Save your file before compiling."));
        return false;
    }
    else if(cur_doc->isModified())
    {
        displaySaveOrIgnoreChanges();
    }

    return compiler->compileRixFile(cur_doc);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool quit = true;

    if(cur_doc->isModified())
        quit = displayUnsavedChanges();

    if(!quit)
    {
        event->ignore();
        return;
    }

    char* temp = sem_error.content; //Used to see the contents of sem_error
    Q_UNUSED(temp)

    // Ensure that the doc is garbage before we post it.
    memset(sem_doc.content, 0, sem_doc.max_size);
    sem_post(sem_doc.sem); // Unblock the child.

    if(child != 0)
    {
        kill(child, SIGTERM);
        wait(NULL);
    }

    CleanUpSharedMemory(&sem_doc, &sem_error);

    QMainWindow::closeEvent(event);
    close();
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
    connect(compiler, SIGNAL(compilerError(QString)),  this, SLOT(readCompilerErrorLine (QString)));
}

void MainWindow::setupTheme()
{
    themer = new ThemeHandler();
    // TODO: Connect the RixLexer and Themer here.
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
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    bool flag = false; // Flag for leaving loop
    bool quit = true;  // Determine if user wants to quit or cancel

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

bool MainWindow::displayAreYouSure(const QString &title, const QString &msg)
{
    QMessageBox msgBox;
    msgBox.setText(title);
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    bool flag = false;
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Yes:
        flag = true;
        break;

    case QMessageBox::No:
        flag = false;
        break;
    }

    return flag;
}

bool MainWindow::displaySaveOrIgnoreChanges()
{

    QMessageBox msgBox;
    msgBox.setText("The document has been previously modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ignore);
    msgBox.setDefaultButton(QMessageBox::Save);

    bool savedChanges = false;
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Save:
        savedChanges = save();
        break;

    case QMessageBox::Ignore:
        savedChanges = false;
        break;
    }

    return savedChanges;
}

void MainWindow::displayErrorMessage(const QString &title, const QString &msg)
{
    QMessageBox::warning(this, title, msg);
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
    cur_index   = index;
    cur_doc     = textEditList[cur_index];
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
    // Don't have multi-tabs; Redirect to save.
    save();
}

void MainWindow::on_button_run_clicked()
{
    runCompiler();
}
