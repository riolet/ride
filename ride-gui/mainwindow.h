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
                void newFile();
                void gotoLine();
                bool runCompiler();
                void loadFile(QString filename);
                
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
#include "Scintilla/scintilladoc.h"
#include "aboutdialog.h"
#include "Compiler/compilerhandler.h"
#include "Scintilla/themehandler.h"

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
    void loadFile(QString filename);
    
    void readCompilerOutputLine(const QString& line);
    void readCompilerErrorLine(const QString& err);
    
    void closeEvent(QCloseEvent *event);
    void sendCloseEvent();

    void tabChanged(int index);
    void documentWasModified();

    private:    //Private Functions
    void setupCompiler();
    void setupFileTree();
    void setupMenuActions();
    void setupScintilla();
    void setupShortcuts(); // Not done yet.
    void setupTheme();
    void setDocumentModified(bool modified);
    void clearCompilerMessages();

private:    //Private Variables
    Ui::MainWindow              *ui;            // Central UI Widget Container
    std::vector<ScintillaDoc*>  textEditList;   // Container of Scintilla widgets
    int                         cur_index;      // Currently active document index
    QFileSystemModel            *model;         // File Directory View
    QTreeView                   *tree;          // File Directory Tree
    ScintillaDoc                *cur_doc;       // Currently active document
    ThemeHandler                *themer;        // Text highlighting manager
    CompilerHandler             *compiler;      // Compilation Handler

};

#endif // MAINWINDOW_H
