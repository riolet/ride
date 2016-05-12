#include <QDebug>
#include <QColor>
#include "rixlexer.h"

RixLexer::RixLexer(QObject *parent) : QsciLexerCustom(parent)
{

}

void RixLexer::handleStyleNeeded(int pos)
{
    if (!editor())
        return;

    int start = editor()->SendScintilla(QsciScintillaBase::SCI_GETENDSTYLED);
    int line = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
            start);
    start = editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
                line);
    qDebug() << "pos:" << pos;
    qDebug() << "start:" << start;
    qDebug() << "line:" << line;

    if (start != pos)
        styleText(start, pos);
}

void RixLexer::styleText(int start, int end)
{
    //char *unstyledChars = (char *) malloc (end - start);

    //editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, lastVisibleCharacter,
    //                        unstyledChars);

    startStyling(start);
    setStyling(end - start, 0);
}

QString RixLexer::description(int style) const
{
    return "Default";
}

const char* RixLexer::language() const
{
    return "Rix";
}
