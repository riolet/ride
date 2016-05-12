#include <QDebug>
#include "rixlexer.h"

void RixLexer::handleStyleNeeded(int pos)
{
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
    //QString source;
    //int i;

    /*if (!editor())
        return;

    char *chars = (char *) malloc (end - start);
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, chars);
    source = QString(chars);
    free(chars);

    qDebug() << "source =" << source;

    startStyling(start, 0x1f);
    QStringList list = source.split("\n");
    for (i = 0; i < list.size(); i++) {
        QString line = list.at(i);
        int len = line.size();
        int style;
        qDebug() << "line =" << line;

        if (line.startsWith("//")) {
            style = Comment;
        } else {
            style = Default;
        }
        qDebug() << "Styling " << len << "bytes " << description(style);
        setStyling(len, getStyle(style));
        // newline character was consumed in split so...
        setStyling(1, getStyle(Default));
    }*/
}

QString RixLexer::description(int style) const
{
    return "Default";
}

const char* RixLexer::language() const
{
    return "Rix";
}
