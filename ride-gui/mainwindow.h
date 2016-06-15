/*===============================================================================
HEADER FILE:    mainwindow.h 
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
                void openProject();
                void newProject();
                void newFile();
                void gotoLine();
                bool runCompiler();
                void loadFile(QString filepath);
                void undo();
                void redo();
                void copy();
                void cut();
                void paste();
                
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
This header file declares all of the functions that are defined inside of the
compilerhandler.cpp file. This class runs the "rix" shell script and sends all
compilation messages to the mainwindow. This is done via signals which are
caught by the mainwindow slot.
===============================================================================*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QApplication>
#include <QCloseEvent>

#include <QFileInfo>
#include <QFileDialog>
#include <QInputDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QSettings>
#include <QSize>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>
#include <QFileSystemModel>
#include <QTreeView>
#include <string>
#include "globals.h"
#include "aboutdialog.h"
#include "Scintilla/scintilladoc.h"
#include "Scintilla/themehandler.h"
#include "Compiler/compilerhandler.h"
#include "Compiler/projecthandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:     //Public Functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

/************************************* 
        Button Click Methods
*************************************/
/*===============================================================================
FUNCTION:       on button open clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_open_clicked()

RETURNS:        Void

NOTES:
Calls the open method. 
===============================================================================*/
    void on_button_open_clicked();

/*===============================================================================
FUNCTION:       on button save clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_save_clicked()

RETURNS:        Void

NOTES:
Calls the save method. 
===============================================================================*/
    void on_button_save_clicked();

/*===============================================================================
FUNCTION:       on button open clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_new_file_clicked()

RETURNS:        Void

NOTES:
Calls the new file method. 
===============================================================================*/
    void on_button_new_file_clicked();

/*===============================================================================
FUNCTION:       on button zoom in clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_zoom_in_clicked()

RETURNS:        Void

NOTES:
Calls the zoom in method. 
===============================================================================*/
    void on_button_zoom_in_clicked();

/*===============================================================================
FUNCTION:       on button zoom out clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_zoom_out_clicked()

RETURNS:        Void

NOTES:
Calls the zoom out method. 
===============================================================================*/
    void on_button_zoom_out_clicked();

/*===============================================================================
FUNCTION:       on button save all clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_saveall_clicked()

RETURNS:        Void

NOTES:
Calls the save all method. 
===============================================================================*/
    void on_button_saveall_clicked();

/*===============================================================================
FUNCTION:       on button run clicked

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void on_button_run_clicked()

RETURNS:        Void

NOTES:
Calls the run compiler method. 
===============================================================================*/
    void on_button_run_clicked();
  

/************************************* 
        Display Message Methods 
*************************************/
/*===============================================================================
FUNCTION:       Display About Rix

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayAboutRix()

RETURNS:        Void

NOTES:
Displays information about the Rix programming Language.

UNFINISHED: Requires Rix information file 
===============================================================================*/
    void displayAboutRix();

/*===============================================================================
FUNCTION:       Display About Ride

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayAboutRide()

RETURNS:        Void

NOTES:
Displays information about the Ride program.

UNFINISHED: Requires Ride information file 
===============================================================================*/
    void displayAboutRide();

/*===============================================================================
FUNCTION:       Display Error Message

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayErrorMessage(const QString &title, 
                                         const QString &msg);

RETURNS:        Void

NOTES:
Creates a generic error message with a supplied title and message body.
===============================================================================*/
    void displayErrorMessage(const QString &title, const QString &msg);

/*===============================================================================
FUNCTION:       Display License

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayLicense()

RETURNS:        Void

NOTES:
Reads in the GNU License Agreement and creates a seperate dialog box displaying
all of the information contained in the text. 
===============================================================================*/
    void displayLicense();

/*===============================================================================
FUNCTION:       Display Save Or Ignore Changes

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool displaySaveOrIgnoreChanges()

RETURNS:        -TRUE   : The user has decided either to save changes.
                -FALSE  : The user selected to ignore their changes.

NOTES:
Displays a message box that will prompt the user to save their current changes
or ignore them.
===============================================================================*/
    bool displaySaveOrIgnoreChanges();

/*===============================================================================
FUNCTION:       Display Unsaved Changes

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayUnsavedChanges()

RETURNS:        -TRUE   : The user has decided either to ignore or save changes.
                -FALSE  : The user selected to cancel the current operation.

NOTES:
Prompts the user with three actions:
    -Close the file without making changes.
    -Save their changes
    -Cancel the current operation
===============================================================================*/
    bool displayUnsavedChanges();

/*===============================================================================
FUNCTION:       display Are You Sure

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool displayAreYouSure (const QString &title,
                                        const QString &msg)

RETURNS:        Void

NOTES:
Prompts the user with a yes or no question. Uses the title and the message to
construct the message box.
===============================================================================*/
     bool displayAreYouSure(const QString &title, const QString &msg);

    
/************************************* 
        Standard IDE functions
*************************************/
/*===============================================================================
FUNCTION:       Save As

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool saveAs()

RETURNS:        -TRUE   : The user has saved their file.
                -FALSE  : The user did not save their file.

NOTES:
Prompts the user to designate where they want to save the file. This will make
a call to the scintilla document to open a new file and save it at that
location. Any errors creating a new file will result in false.
===============================================================================*/
    bool saveAs();

/*===============================================================================
FUNCTION:       Save

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool save()

RETURNS:        -TRUE   : The user has saved their file.
                -FALSE  : The user did not save their file.

NOTES:
Checks if the current document is blank where it will be redirected to saveAs
if it is. Otherwise, it will attempt to save the already opened file.
===============================================================================*/
    bool save();

/*===============================================================================
FUNCTION:       Undo

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void undo()

RETURNS:        Void

NOTES:
When the scintilla document is not in focus, it sends the undo command to the
scintilla as if it were in focused by the user.
===============================================================================*/
    void undo();

/*===============================================================================
FUNCTION:       Redo

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void redo()

RETURNS:        Void

NOTES:
When the scintilla document is not in focus, it sends the redo command to the
scintilla as if it were in focused by the user.
===============================================================================*/
    void redo();

/*===============================================================================
FUNCTION:       Open

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void open()

RETURNS:        Void

NOTES:
Prompts the user to select a file to be opened and attempts to load the file's
contents onto the scintilla edit text surface.
===============================================================================*/
    void open();

/*===============================================================================
FUNCTION:       Open Project

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void openProject()

RETURNS:        Void

NOTES:
Prompts the user to select a file with the '.prox' file extension to be opened
and attempts to load the file's contents using the Project Handler.
===============================================================================*/
    void openProject();

/*===============================================================================
FUNCTION:       New Project

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void openProject()

RETURNS:        Void

NOTES:
Creates a new project for the user by prompting the user where they want to
create the project.
===============================================================================*/
    void newProject();

/*===============================================================================
FUNCTION:       New File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void newFile()

RETURNS:        -TRUE   : The user has decided either to ignore or save changes.
                -FALSE  : The user selected to cancel the current operation.

NOTES:
Clears the text surface
UNFINISHED: Add in another tab widget and create a new blank document.
            Currently clears the contents of the scintilla edit text surface
            which is undesirable.
===============================================================================*/
    void newFile();

/*===============================================================================
FUNCTION:       Go to Line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void gotoLine()

NOTES:
Prompts the user with what line they wish to go to and makes their text cursor
travel to the appropriate line.
===============================================================================*/
    void gotoLine();

/*===============================================================================
FUNCTION:       Copy

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void copy()

NOTES:
Copy the selected text.
===============================================================================*/
    void copy();

/*===============================================================================
FUNCTION:       Go to Line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void cut()

NOTES:
Cut the selected text.
===============================================================================*/
    void cut();

/*===============================================================================
FUNCTION:       Go to Line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void paste()

NOTES:
Paste the selected text at the text cursor.
===============================================================================*/
    void paste();

/*===============================================================================
FUNCTION:       Run Compiler

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool runCompiler()

RETURNS:        -TRUE   : Successful compilation.
                -FALSE  : There was an error with compilation.

NOTES:
Clears all of the compilation messages and uses its compiler to compile the
current document.
===============================================================================*/
    bool runCompiler();

/*===============================================================================
FUNCTION:       Load File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void displayUnsavedChanges()

RETURNS:        Void

NOTES:
Uses a file's absolute file path and attempts to load the file's content onto
the scintilla text edit surface. Any errors when loading the file will display
an error message indicating a file load failure.
===============================================================================*/
    void loadFile(QString filepath);
    

/******************************************** 
      Qt Slots that handle Qt Signals
********************************************/
/*===============================================================================
FUNCTION:       Read Compiler Output Line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void readCompilerOutputLine(const QString& line)

PARAMETERS:     const QString& line
                    Standard output line message.

RETURNS:        Void

NOTES:
This is a signal handler that catches the compilerOutput(QString) signal and
sends the line of compiler output into the output tab.
===============================================================================*/
    void readCompilerOutputLine(const QString& line);

/*===============================================================================
FUNCTION:       Read Compiler Error Line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void readCompilerErrorLine(const QString& err)

PARAMETERS:     const QString& err
                    Standard error line message.

RETURNS:        Void

NOTES:
This is a signal handler that catches the compilerError(QString) signal and
sends the line of compiler error into the issues tab.
===============================================================================*/
    void readCompilerErrorLine(const QString& err);
    
/*===============================================================================
FUNCTION:       Close Event

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void closeEvent(QCloseEvent *event)

PARAMETERS:     QCloseEvent *event
                    The caught close event to be handled.

RETURNS:        Void

NOTES:
This is the close event signal handler. First it checks whether or not the 
document that the user was working on was modified and prompts for user action.
After that, it handles dealing with unblocking the child process that detects 
errors and sends the kill signal to that process and destroying the used
semaphores.
===============================================================================*/
    void closeEvent(QCloseEvent *event);

/*===============================================================================
FUNCTION:       Send Close Event

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void sendCloseEvent()

RETURNS:        Void

NOTES:
Creates a new close event signal and calls the closeEvent(QCloseEvent*) method.
===============================================================================*/
    void sendCloseEvent();

/*===============================================================================
FUNCTION:       Tab Changed

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void tabChanged(int index)

PARAMETERS:     int index
                    Index of the new tab.

RETURNS:        Void

NOTES:
This slot detects whenever the tab has changed in regarded to scintilla and
changes the "cur_doc" to the new tab that was selected.

UNFINISHED: Multiple tabs was not implemented but this will take care of
            handling of changing the current document to the new tab which will
            contain the new document.
===============================================================================*/
    void tabChanged(int index);

/*===============================================================================
FUNCTION:       Document Was Modified

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void documentWasModified()

RETURNS:        Void

NOTES:
Signal catcher used to handle when a document was modified. Upon modification,
the tab text for the current document will contain a star and other options
will open up to prevent running or closing an unsaved modified file.
===============================================================================*/
    void documentWasModified();

    private:    //Private Functions
/*===============================================================================
FUNCTION:       Set Up Compiler

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupCompiler()

RETURNS:        Void

NOTES:
Creates a new compiler handler and sends all compilation message to the output
or error tabs.
===============================================================================*/
    void setupCompiler();

/*===============================================================================
FUNCTION:       Set up File Tree

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupFileTree()

RETURNS:        Void

NOTES:
Populates the file tree with the directory and file contents depending on where
this application was launched.

UNFINISHED: The file tree should indicate which files belong to their
            projects and should contain multiple projects.
===============================================================================*/
    void setupFileTree();

/*===============================================================================
FUNCTION:       Set up Menu Actions

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupMenuActions()

RETURNS:        Void

NOTES:
Connects the menu actions with their appropriate method to call.

UNFINISHED: The About Rix and About Ride actions are set up to call the proper
            functions but the functions are currently empty.
===============================================================================*/
    void setupMenuActions();

/*===============================================================================
FUNCTION:       Set up Scintilla

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupScintilla()

RETURNS:        Void

NOTES:
Removes all initial unused tabs from the mainwindow and creates a new blank
tab.
===============================================================================*/
    void setupScintilla();

/*===============================================================================
FUNCTION:       Set up Shortcuts

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupShortcuts()

RETURNS:        Void

NOTES:
Connects common actions to a desired keyboard shortcut.
===============================================================================*/
    void setupShortcuts();

/*===============================================================================
FUNCTION:       Set up File Tree

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setupTheme()

RETURNS:        Void

NOTES:
Initializes the theme handler and uses the default colour scheme.

UNFINISHED: Does not connect to the RixLexer at the moment and having multiple
            themes has not been built yet.
===============================================================================*/
    void setupTheme();

/*===============================================================================
FUNCTION:       Set Document Modified

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setDocumentModified(bool modified)

PARAMETERS:     bool modified
                    Flag to remove or set the star in the current document's
                    tab text.

RETURNS:        Void

NOTES:
Sets or removes a star character in the tab text of the current scintilla
document.
===============================================================================*/
    void setDocumentModified(bool modified);

/*===============================================================================
FUNCTION:       Clear Compiler Messages

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void clearCompilerMessages()

RETURNS:        Void

NOTES:
Clears all compilation messages from the output and the issues tabs.
===============================================================================*/
    void clearCompilerMessages();

private:    //Private Variables
    Ui::MainWindow              *ui;            // Central UI Widget Container
    std::vector<ScintillaDoc*>  textEditList;   // Container of Scintilla widgets
    ScintillaDoc                *cur_doc;       // Currently active document
    int                         cur_index;      // Currently active document index
    QFileSystemModel            *model;         // File Directory View
    QTreeView                   *tree;          // File Directory Tree
    ThemeHandler                *themer;        // Text highlighting manager
    CompilerHandler             *compiler;      // Compilation Handler
    ProjectHandler              *project;       // Project handler

};

#endif // MAINWINDOW_H
