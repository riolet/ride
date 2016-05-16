#ifndef RIXLEXER_H
#define RIXLEXER_H

#include <QColor>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <stdio.h>
#include "globals.h"

extern void scan_string(const char* str);

class RixLexer : public QsciLexerCustom
{
    Q_OBJECT
public:
    RixLexer(QObject *parent = 0);
    void styleText(int start, int end);
    QString description(int style) const;
    const char* language() const;
private slots:
    void handleStyleNeeded(int pos);
};

#endif // RIXLEXER_H
