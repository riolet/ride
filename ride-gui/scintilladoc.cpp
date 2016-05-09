#include "scintilladoc.h"

bool ScintillaDoc::loadFile(QString filepath)
{
    _file = new QFile(filepath);
    _filepath = _file->fileName();
    if (!_file->open(QFile::ReadOnly))
    {
        _errorString = _file->errorString();
        return false;
    }

    // Qt's naming scheme is very odd.
    _filename = QFileInfo(_file->fileName()).fileName();

    QTextStream in(_file);
    _editText->setText(in.readAll());

    _file->close();
    _isBlank = false;
    return true;
}

bool ScintillaDoc::saveFile(QString newFilePath)
{
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

    return true;
}

bool ScintillaDoc::saveAs(QString filepath)
{
    if (filepath.isEmpty())
        return false;

    _filename = filepath;
    return saveFile(filepath);
}

bool ScintillaDoc::isBlank()
{
    return _isBlank;
}
