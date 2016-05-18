#include "rixlexer.h"

void RixLexer::handleStyleNeeded(int pos)
{
    if (!editor())
        return;

    int start   = editor()->SendScintilla(QsciScintillaBase::SCI_GETENDSTYLED);
    int line    = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
                                            start);
    start       = editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
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

void RixLexer::handleCharAdded(int pos)
{
    if (pos <= 0)
        return;

    char charAtPos[1];
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, pos - 1, pos, charAtPos);

    if (charAtPos[0] == '.')
    {
        int line        = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
                                                    pos);
        int lineStart   = editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
                                                    line);

        char lineChars[pos - lineStart];
        editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, lineStart, pos, lineChars);


    }
}

QString RixLexer::description(int style) const
{
    switch (style)
    {
    case 1:
        return "Integer";
    case 2:
        return "Float";
    case 3:
        return "Int";
    case 4:
        return "String";
    case 5:
        return "Char";
    case 6:
        return "Class";
    case 7:
        return "Scope";
    case 8:
        return "Keyword";
    case 9:
        return "Return";
    case 10:
        return "Identifier";
    case 11:
        return "Single-line comment";
    case 12:
        return "Terminated multi-line comment";
    case 13:
        return "Unterminated multi-line comment";
    default:
        return "Unknown";
    }

    return NULL;
}

const char* RixLexer::language() const
{
    return "Rix";
}

const char* RixLexer::lexer() const
{
    return "RixLexer";
}
