#include "rixlexer.h"
#include "syntaxcolours.h"

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

void RixLexer::setScintilladoc(ScintillaDoc *sd)
{
    _scint = sd;
}

void RixLexer::styleText(int start, int end)
{
    if(end < start || !editor())
        return;

    char chars[end - start];
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end,
                            chars);

    startStyling(start);
    scan_string(chars);
}

void RixLexer::styleToken(int length, int style)
{
    if (style == SyntaxColours::Default)
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

    char currentChar[1];
    int wordEnd = editor()->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS) - 1;
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, wordEnd, wordEnd + 1, currentChar);
    if (currentChar[0] == '.')
    {
        bool onlyWordCharacters = true;
        int wordStart = editor()->SendScintilla(QsciScintillaBase::SCI_WORDSTARTPOSITION,
                                                wordEnd, onlyWordCharacters);

        char word[wordEnd - wordStart + 1];
        editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE,
                                wordStart, wordEnd, word);

        // Call function to get methods of "word" here
        // Return must be a const c-string, with functions
        // & members separated by spaces
        const char *testing = "test test1 test2 test3";

        editor()->SendScintilla(QsciScintilla::SCI_AUTOCSHOW, (size_t)0, testing);
    }
    else if(currentChar[0] == '\n')
    {
        //_scint->parseError();
        //handleFoundErrors();
    }
}

void RixLexer::handleFoundErrors()
{
    Error*  cur_error;
    char*   msg;
    int     len;
    int     line;
    int     start;
    int     num;

    int errors = sem_error.errNumber;

    while(errors > 0)
    {
        cur_error = sem_error.content[0];

        msg = cur_error->message;
        line = cur_error->line_number;
        start = cur_error->column_start;
        num = cur_error->num_characters;
        len = cur_error->message_length;

        // TODO: Call highlight method here.
        //method(msg, len, line, start, num);

        errors--; // Decrement errors here.
    }
}

void RixLexer::setWordChars(char *chars)
{
    if (!editor())
        return;

    editor()->SendScintilla(QsciScintillaBase::SCI_SETWORDCHARS,
                            chars);
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
    case 14:
        return "Function declaration";
    case 15:
        return "Return type";
    case 16:
        return "Function call";
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
