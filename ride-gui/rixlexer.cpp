#include <QDebug>
#include <QColor>
#include <QString>
#include "rixlexer.h"

RixLexer::RixLexer(QObject *parent) : QsciLexerCustom(parent)
{

}

void RixLexer::handleStyleNeeded(int pos)
{
    if (!editor())
        return;

    int start = editor()->SendScintilla(QsciScintillaBase::SCI_GETENDSTYLED);
    int line =  editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
                start);
    start =     editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
                line);

    if (start != pos)
        styleText(start, pos);
}

void RixLexer::styleText(int start, int end)
{
    char *unstyledChars = (char *) malloc (end - start);

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end,
                            unstyledChars);
    qDebug() << QString::fromLatin1(unstyledChars);

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
