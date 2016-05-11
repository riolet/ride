#include "scintilladoc.h"

ScintillaDoc::ScintillaDoc(QObject *parent) : QObject(parent)
{
    _filename = QString("untitled");
    _editText = new QsciScintilla;
    _isBlank = true;
    _modified = false;
    _filepath = QString("");

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
