#ifndef CUSTOMSCINTILLA_H
#define CUSTOMSCINTILLA_H

#include <QObject>
#include <QWidget>
#include <Qsci/qsciscintilla.h>
#include "scintilladoc.h"

class ScintillaDoc;

class CustomScintilla : public QsciScintilla
{
public:
    CustomScintilla(ScintillaDoc* parent);

    bool eventFilter(QObject *obj, QEvent *event);
    ScintillaDoc* _doc;
};

#endif // CUSTOMSCINTILLA_H
