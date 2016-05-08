#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QString>
#include <Qsci/qsciscintilla.h>

class ScintillaDoc
{
public:
    ScintillaDoc()
        : _doc(new QsciScintilla), _name(QString("untitled"))
    {

    }

    ScintillaDoc(QsciScintilla* doc, QString name = QString("untitled"))
        : _doc(doc), _name(name)
    {

    }

public: // public variables
    QsciScintilla*  _doc;
    QString         _name;
};

#endif // SCINTILLADOC_H
