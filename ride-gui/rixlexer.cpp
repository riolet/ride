#include "rixlexer.h"

RixLexer::RixLexer (QObject *parent) : QsciLexerCustom(parent)
{
    scan_string("int i = 3");
    fflush(stdout);
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
    //qDebug() << "pos:" << pos;
    //qDebug() << "start:" << start;
    //qDebug() << "line:" << line;

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
    std::string unstyledChars(chars);
    //qDebug() << QString::fromStdString(unstyledChars);

    startStyling(start);
    setStyling(end - start, 0);
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
