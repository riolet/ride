#include "rixlexer.h"

void RixLexer::RixLexer (QObject *parent) : QsciLexerCustom(parent)
{
    char output[10];
    yyin = fopen("test.txt", "w+");
    fputs("int i = 3", yyin);
    fflush(stdout);
    fgets(output, 9, yyin);
    printf("File contents pre-lexing: %s\n", output);
    qDebug() << "File contents pre-lexing:" << QString::fromLatin1(output);
    fflush(stdout);
    yylex();
    fflush(stdout);
    fgets(output, 9, yyin);
    printf("File contents pre-lexing: %s\n", output);
    fflush(stdout);
}

void RixLexer::~RixLexer()
{
    fclose(yyin);
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
    char chars[end - start];

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end,
                            chars);
    std::string unstyledChars(chars);
    qDebug() << QString::fromStdString(unstyledChars);

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
