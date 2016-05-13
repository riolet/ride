#ifndef RIXLEXER_H
#define RIXLEXER_H

#include <QColor>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <stdio.h>
#include "globals.h"

extern int yylex();
extern FILE *yyin;

class RixLexer : public QsciLexerCustom
{
    Q_OBJECT
public:
    RixLexer(QObject *parent = 0);
    ~RixLexer();
    void styleText(int start, int end) override;
    QString description(int style) const override;
    const char* language() const override;
private slots:
    void handleStyleNeeded(int pos);
};

#endif // RIXLEXER_H