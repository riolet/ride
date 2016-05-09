#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>
#include "globals.h"

class ScintillaDoc
{
public:
    //Default constructor
    ScintillaDoc()
        : _editText(new QsciScintilla), _filename(QString("untitled"))
    {
        _isBlank = true;
        _filepath = QString("");
    }

    //Constructor with a previously existing scintilla document
    ScintillaDoc(QsciScintilla* doc, QString name = QString("untitled"))
        : _editText(doc), _filename(name)
    {
        _isBlank = true;
        if(_filename == QString("untitled"))
        {
            _isBlank = true;
            _filepath = QString("");
        }
    }


    bool loadFile(QString filepath);

    bool saveFile(QString newFilePath = QString(""));

    bool saveAs(QString filepath);

    bool isBlank();

private: // Private functions


public: // public variables
    QsciScintilla*  _editText;
    QString         _filename;
    QString         _filepath;
    QString         _errorString;
    QFile*          _file;

private:
    bool            _isBlank;
};

#endif // SCINTILLADOC_H

