#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>
#include "globals.h"

class ScintillaDoc
{
public:
    ScintillaDoc()
        : _editText(new QsciScintilla), _filename(QString("untitled"))
    {

    }

    ScintillaDoc(QsciScintilla* doc, QString name = QString("untitled"))
        : _editText(doc), _filename(name)
    {

    }

    bool loadFile(QString &filepath);


public: // public variables
    QsciScintilla*  _editText;
    QString         _filename;
    QString         _errorString;
    QFile*          _file;
};

#endif // SCINTILLADOC_H

