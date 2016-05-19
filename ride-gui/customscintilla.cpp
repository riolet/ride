#include "customscintilla.h"
#include <QDebug>
#include <QKeyEvent>

int i = 2;

CustomScintilla::CustomScintilla(ScintillaDoc *parent)
    : QsciScintilla(parent), _doc(parent)
{
    installEventFilter(this);
}

bool CustomScintilla::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) )
            {
                qDebug() << "Tyler is a rude dude." << i;
                i++;
                // Custom event handling here.
            }
        }
    }
    return QsciScintilla::eventFilter(obj, event);
}
