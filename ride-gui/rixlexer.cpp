#include "rixlexer.h"
#include <QDebug>

void RixLexer::handleStyleNeeded(int pos)
{
    if (!editor())
        return;

    int start = editor()->SendScintilla(QsciScintillaBase::SCI_GETENDSTYLED);
    int line = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
            start);
    start = editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
                line);

    if (start != pos)
        styleText(start, pos);
}

void RixLexer::styleText(int start, int end)
{
    if(end < start)
        return;

    char chars[end - start];

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end,
                            chars);

    startStyling(start);
    scan_string(chars);
}

void RixLexer::styleToken(int length, int style)
{
    if (style == 0)
    {
        setStyling(length, 32);
        return;
    }
    setStyling(length, style);
}

QString RixLexer::description(int style) const
{
    Q_UNUSED(style);
    return "Default";
}

const char* RixLexer::language() const
{
    return "Rix";
}
