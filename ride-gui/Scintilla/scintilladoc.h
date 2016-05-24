/*===============================================================================
HEADER FILE:    scintilladoc.h 
                    Class dedicated to handling all operations within the
                    scintilla document and the files that represent them.

PROGRAM:        Ride

FUNCTIONS:      explicit ScintillaDoc(QWidget *parent = 0);
                bool loadFile(QString filepath);
                bool saveFile(QString newFilePath = QString(""));
                bool saveAs(QString filepath);
                void clearTextArea();
                bool isBlank();
                bool isModified();
                void zoom_in();
                void zoom_out();
                void gotoLine(int line);
                int getTotalLines();
                const QString getAllText();
                void setWrapMode(bool enable);
                void scintillaTextChanged();

QT SIGNALS:     void textChanged();

PROGRAMMER(S):  Tyler Trepanier-Bracken

NOTES:
This header file declares all of the functions that are defined inside of the
scintilla.cpp file. The purpose of this class is to encapsulate all methods
that deal with the text edit surface, seperating the concerns of the 
mainwindow and scintilla.
===============================================================================*/

#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QObject>
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>
#include <QShortcut>
#include "globals.h"
#include "lexershare.h"

#define ZOOM_FACTOR 2                   // Zoom factor for zooming in/out.
#define MARGIN_WIDTH QString("123456")  // Width for the number margin

class ScintillaDoc : public QWidget
{
    Q_OBJECT
public:

    //Only this version of the constructor is allowed.
    explicit ScintillaDoc(QWidget *parent = 0);

/*===============================================================================
FUNCTION:       Load File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool loadFile(QString filepath)

PARAMETERS:     QString filepath
                    File path of the file to be loaded onto scintilla.

RETURNS:        -TRUE   : successful file loading and displays it onto scintilla
                -FALSE  : unsuccessful file loading.

NOTES:
Attempts to load a file from the specified filepath and returns the result. 
===============================================================================*/
    bool loadFile(QString filepath);

/*===============================================================================
FUNCTION:       Save File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool saveFile(QString newFilePath = QString(""));

PARAMETERS:     QString newFilePath
                    (Unimplemented at the moment)

RETURNS:        -TRUE   : Successful saving the scintilla document onto its 
                          file.
                -FALSE  : File was not saved to its assigned file.

NOTES:
Saves the contents of the scintilla document inside of its assign file.
===============================================================================*/
    bool saveFile(QString newFilePath = QString(""));

/*===============================================================================
FUNCTION:       Save As

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool saveAs(QString filepath)

PARAMETERS:     QString filepath
                    Desired location for a file to be saved in the file system.

RETURNS:        -TRUE   : Successful saving the scintilla document onto its 
                          file.
                -FALSE  : File was not saved to its assigned file.

NOTES:
Uses the desired filepath and returns the result of save().
===============================================================================*/
    bool saveAs(QString filepath);

/*===============================================================================
FUNCTION:       Clear Text Area

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void clearTextArea()

RETURNS:        Void

NOTES:
Clears the scintilla document of all text.
===============================================================================*/
    void clearTextArea();

/*===============================================================================
FUNCTION:       Is Blank

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool isBlank()

RETURNS:        -TRUE   : The current document is an unsaved blank file.
                -FALSE  : The current document is an actual file.

NOTES:
Whether or not the document is a new blank document. 
===============================================================================*/
    bool isBlank();

/*===============================================================================
FUNCTION:       Is Modified

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool isModified()

RETURNS:        -TRUE   : The document was changed on the text edit surface.
                -FALSE  : The document was not changed since the last save.

NOTES:
Checks if the document was modified since its last save.
===============================================================================*/
    bool isModified();

/*===============================================================================
FUNCTION:       Zoom In

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void zoom_in()

RETURNS:        Void

NOTES:
Increases the font size of the text edit surface by the ZOOM FACTOR.  
===============================================================================*/
    void zoom_in();

/*===============================================================================
FUNCTION:       Zoom Out

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void zoom_out()

RETURNS:        Void

NOTES:
Decreases the font size of the text edit surface by the ZOOM FACTOR.  
===============================================================================*/
    void zoom_out();

/*===============================================================================
FUNCTION:       Go to line

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void gotoLine(int line)

PARAMETERS:     int line
                    Desired line to send the text cursor to.

RETURNS:        Void

NOTES:
Sends the text cursor to the specified line.  
===============================================================================*/
    void gotoLine(int line);

/*===============================================================================
FUNCTION:       Copy

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void copy()

NOTES:
Copy the selected text.
===============================================================================*/
        void copy();

/*===============================================================================
FUNCTION:       Cut

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void cut()

NOTES:
Cut the selected text.
===============================================================================*/
        void cut();

/*===============================================================================
FUNCTION:       Paste

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void paste()

NOTES:
Paste the selected text at the text cursor.
===============================================================================*/
        void paste();

/*===============================================================================
FUNCTION:       Get Total Lines

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int getTotalLines()

RETURNS:        int : Total number of lines in the current scintilla document.

NOTES:
Returns the total number of lines in the current scintilla document.
===============================================================================*/
    int getTotalLines();

/*===============================================================================
FUNCTION:       Get All Text

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      const QString getAllText()

RETURNS:        const QString  : All the text on the scintilla document 
                                    (not actual file contents)

NOTES:
Gathers all of the text inside scintilla document and returns it.
===============================================================================*/
    const QString getAllText();

/*===============================================================================
FUNCTION:       Parse Error

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void parseError()

RETURNS:        Void

NOTES:
Gathers all of the current text and informs the error detector that there is
text to be parsed using semaphores. This function makes use of the semaphore
"sem_doc" and as such, results in a delayed mainwindow response until the error
detection has completed.
===============================================================================*/
    void parseError();

private: // Private functions

/*===============================================================================
FUNCTION:       Set Wrap Mode

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setWrapMode(bool enable)

PARAMETERS:     bool enable
                    flag to set the text wrap to on or off.

RETURNS:        Void

NOTES:
NOT IMPLEMENTED IN THE CURRENT CODE BUT WORKING. Flag that sets text wrap to
either on or off.  
===============================================================================*/
    void setWrapMode(bool enable); 

signals:

/*===============================================================================
QT SIGNAL:      Text Changed

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void textChanged()

RETURNS:        Void

NOTES:
Signal to be caught by another QObject to indicate that text has changed.
===============================================================================*/
    void textChanged();

private slots:

/*===============================================================================
FUNCTION:       Scintilla Text Changed

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void scintillaTextChanged()

RETURNS:        Void

NOTES:
Catches the QScintilla signal for "textChanged()" and determines whether or
not to send the signal to the mainwindow. Sending to the mainwindow multiple
times is unnecessary.
===============================================================================*/
    void scintillaTextChanged();

public: // public variables
    QsciScintilla*      _editText;      // Actual scintilla document.
    QString             _filename;      // Name of the file being worked on.
    QString             _filepath;      // Absolute file path of the file.
    QString             _errorString;   // Current error
    QFile*              _file;          // QFile containing the file's contents.
    QShortcut*          _autoShort;      // Shortcut key binding for autocomplete

private: // private variables
    bool            _isBlank;           // Blank file flag.
    bool            _modified;          // Modified file flag.
};

#endif // SCINTILLADOC_H

