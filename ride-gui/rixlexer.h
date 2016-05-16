#ifndef RIXLEXER_H
#define RIXLEXER_H

#include <QColor>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <stdio.h>

extern void scan_string(const char* str);

class RixLexer : public QsciLexerCustom
{
    Q_OBJECT
public:
    void styleText(int start, int end) override;
    void styleToken(int length, int style);
    QString description(int style) const override;
    const char* language() const override;
private slots:
    void handleStyleNeeded(int pos);
};

#endif // RIXLEXER_H
