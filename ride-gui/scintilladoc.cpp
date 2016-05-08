#include "scintilladoc.h"

bool ScintillaDoc::loadFile(QString &filepath)
{
    _file = new QFile(filepath);
    if (!_file->open(QFile::ReadOnly))
    {
        _errorString = _file->errorString();

        delete _file;
        return false;
    }

    // Qt's naming scheme is very odd.
    _filename = QFileInfo(_file->fileName()).fileName();

    QTextStream in(_file);
    _editText->setText(in.readAll());

    return true;
}
