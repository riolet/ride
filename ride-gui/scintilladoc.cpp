#include "scintilladoc.h"
#include <QDebug>

ScintillaDoc::ScintillaDoc(QObject *parent) : QObject(parent)
{
    _lex = new RixLexer;
    _filename = QString("untitled");
    _editText = new QsciScintilla;
    _isBlank = true;
    _modified = false;
    _filepath = QString("");

    _lex->setEditor(_editText);
    int numSyntaxColors = (sizeof(_lex->syntaxColors) / sizeof(_lex->syntaxColors[0])) - 1;

    qDebug() << "numSyntaxColors:" << numSyntaxColors;
    for (int i = 1; i <= numSyntaxColors; i++)
    {
        _lex->editor()->SendScintilla(QsciScintilla::SCI_STYLESETFORE,
                                      i, _lex->syntaxColors[i]);
    }

    connect(_editText,SIGNAL(SCN_CHARADDED(int)),
                 _lex, SLOT(handleCharAdded(int)));

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
    _file = new QFile(filepath);
    _filepath = _file->fileName();
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
    _isBlank = false;
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
    if (filepath.isEmpty())
        return false;

    _file = new QFile(filepath);
    _filename = QFileInfo(_file->fileName()).fileName();
    _filepath = filepath;

    _isBlank = false;
    _modified = false;

    return saveFile(filepath);
}

void ScintillaDoc::clearTextArea()
{
    _editText->clear();
    _filename = QString("untitled");
    _isBlank = true;
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

int ScintillaDoc::getTotalLines()
{
    return _editText->lines();
}

const QString ScintillaDoc::getAllText()
{
    long num_total = _editText->SendScintilla(QsciScintilla::SCI_GETTEXTLENGTH);
    char all_text[num_total];
    long num_copied = _editText->SendScintilla(QsciScintilla::SCI_GETTEXT, num_total, all_text);

    if( (num_copied+1) != num_total)
    {
        // Error occured, the total characters available was not copied correctly.
        return QString("Tacobell");
    }

    /* Placeholder code for detecting errors.
    Error* error_array;
    int num_errors;

    int error = errorDetect(&error_array, &num_errors, all_text);
    */
    QString temp(all_text);
    return temp;
}

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

void ScintillaDoc::handleFoundErrors()
{
    // TODO: implement error wrapping functionality.
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
