/*===============================================================================
SOURCE FILE:    scintilladoc.cpp 
                    Definition file dedicated to handling all operations within 
                    the scintilla document and the files that represent them.

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
This source file defines all of the functions that are declared inside of the
scintilla.h file. The purpose of this class is to encapsulate all methods
that deal with the text edit surface, seperating the concerns of the 
mainwindow and scintilla.
===============================================================================*/

#include "scintilladoc.h"
#include "syntaxcolours.h"

struct error_object** errors;
int* err_num;

ScintillaDoc::ScintillaDoc(QWidget *parent) : QWidget(parent)
{
    _filename   = QString("untitled");
    _editText   = new QsciScintilla;
    _lex        = new RixLexer;
    _isBlank    = true;
    _modified   = false;
    _filepath   = QString("");
    _autoShort  = new QShortcut(QKeySequence("Ctrl+Space"), _editText);

    _lex->setEditor(_editText);
    _lex->setScintilladoc(this);
    _lex->setErrorStyle(0, 1, 0x000099); // 1 = INDIC_SQUIGGLE

    int numSyntaxColors = sizeof(SyntaxColours::colourValues) / sizeof(SyntaxColours::colourValues[0]);

    // Sets the styles for each syntax type.
    // Can't do this inside RixLexer; application crashes
    for (int i = 0; i < numSyntaxColors; i++)
    {
        _lex->editor()->SendScintilla(QsciScintilla::SCI_STYLESETFORE,
                                      i, SyntaxColours::colourValues[i]);
    }
    _lex->editor()->SendScintilla(QsciScintilla::SCI_SETCHARSDEFAULT);

    connect(_editText,SIGNAL(SCN_CHARADDED(int)),
                 _lex, SLOT(handleCharAdded(int)));
    connect(_autoShort, SIGNAL(activated()),
                _lex, SLOT(autoCompleteShortcut()));

    connect(_editText, SIGNAL(textChanged()),
                this, SLOT(scintillaTextChanged()));

    QFont fixedfont("Monospace", 12);
    fixedfont.setStyleHint(QFont::Monospace);

    _editText->setAutoIndent(true);
    _editText->setFont(fixedfont);
    _editText->setMarginLineNumbers(1, true);
    _editText->setMarginWidth(1, MARGIN_WIDTH); // 6 characters wide.
}

bool ScintillaDoc::loadFile(QString filepath)
{
    _file       = new QFile(filepath);
    _filepath   = _file->fileName();

    if (!_file->open(QFile::ReadOnly))
    {
        delete _file;
        _errorString = _file->errorString();
        return false;
    }

    // Qt's naming scheme is very odd.
    _filename = QFileInfo(_file->fileName()).fileName();

    QTextStream in(_file);
    _editText->setText(in.readAll());

    _file->close();

    _isBlank  = false;
    _modified = false;

    return true;
}

bool ScintillaDoc::saveFile(QString newFilePath)
{
    Q_UNUSED(newFilePath);
    /*
     *TODO: Rename files with their new file name.
     */

    /*QString filename = _filename;
    if(!newFileName.isEmpty())
    {
        filename = newFileName;
    }*/

    if(_isBlank)
    {
        _errorString = QString("Cannot handle saving blank files currently");
        return false;
    }

    if (!_file->open(QFile::WriteOnly))
    {
        _errorString = _file->errorString();
        return false;
    }

    QTextStream out(_file);
    out << _editText->text();

    _file->close();
    _modified = false;

    return true;
}

bool ScintillaDoc::saveAs(QString filepath)
{
    if (filepath.isEmpty() || filepath.isNull())
        return false;

    _file       = new QFile(filepath);
    _filename   = QFileInfo(_file->fileName()).fileName();
    _filepath   = filepath;

    _isBlank    = false;
    _modified   = false;

    return saveFile(filepath);
}

void ScintillaDoc::clearTextArea()
{
    _editText->clear();
    _filename = QString("untitled");
    _isBlank  = true;
    _modified = false;
}

bool ScintillaDoc::isBlank()
{
    return _isBlank;
}

bool ScintillaDoc::isModified()
{
    return _modified;
}

void ScintillaDoc::zoom_in()
{
    _editText->zoomIn(ZOOM_FACTOR);
}

void ScintillaDoc::zoom_out()
{
    _editText->zoomOut(ZOOM_FACTOR);
}

void ScintillaDoc::gotoLine(int line)
{
    _editText->setCursorPosition((line - 1), 0);
}

void ScintillaDoc::copy()
{
    if(_editText->hasSelectedText())
    {
        _editText->copy();
    }
}

void ScintillaDoc::cut()
{
    if(_editText->hasSelectedText())
    {
        _editText->cut();
    }
}

void ScintillaDoc::paste()
{
    _editText->paste();
}

int ScintillaDoc::getTotalLines()
{
    return _editText->lines();
}

const QString ScintillaDoc::getAllText()
{
    long num_total = _editText->SendScintilla(QsciScintilla::SCI_GETTEXTLENGTH);
    if(num_total < 1)
    {
        return QString("");
    }

    char all_text[num_total];
    long num_copied = _editText->SendScintilla(QsciScintilla::SCI_GETTEXT, num_total, all_text);

    if( (num_copied+1) != num_total)
    {
        // Error occured, the total characters available was not copied correctly.
        return QString("");
    }

    QString temp(all_text);
    return temp;
}

void ScintillaDoc::parseError()
{
    QString text = getAllText();
    int size = text.length();
    if(text.isEmpty() || text.isNull())
    {
        return;
    }

    //semaphore_request start_doc = sem_doc;
    //semaphore_response start_err = sem_error;

    int result;
    if(text.length() > sem_doc.max_size)
    {
        result = RemapSharedMemory(&sem_doc, &sem_error, size + 1);

        if(result != (size+1))
        {
            std::cerr << "Critical error, could not remap the shared memory." << std::endl;
        }
    }

    //semaphore_request  end_doc = sem_doc;
    //semaphore_response end_err = sem_error;

    // START WRITING TO TEMP DOC
    printf("Writing to shared memory\n");
    sprintf(sem_doc.content, "%s", text.toStdString().c_str());
    printf("Sem post, finished writing to document.\n");

    sem_post(sem_doc.sem);   // END OF TEMP DOC WRITING

    sem_wait(sem_error.sem); // GRAB THE ERROR HERE
}

// Working but it is not implemented yet.
void ScintillaDoc::setWrapMode(bool enable)
{
    if(enable)
    {
        _editText->setWrapMode(_editText->WrapWord);
    }
    else
    {
        _editText->setWrapMode(_editText->WrapNone);
    }
}

void ScintillaDoc::scintillaTextChanged()
{

    if(_modified)
    {
        return;
    }

    _modified = true;
    emit textChanged();
}
