#ifndef RIXLEXER_H
#define RIXLEXER_H

#include <QColor>
#include <QStringList>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <stdio.h>

extern void scan_string(const char* str);

class RixLexer : public QsciLexerCustom
{
    Q_OBJECT

public:
    void styleText(int start, int end);
    void styleToken(int length, int style);
    void setWordChars(char *chars);
    QString description(int style) const;
    const char* language() const;
    const char* lexer() const;

private slots:
    void handleStyleNeeded(int pos);
    void handleCharAdded(int pos);
};

#endif // RIXLEXER_H
