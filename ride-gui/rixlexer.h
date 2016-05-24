#ifndef RIXLEXER_H
#define RIXLEXER_H

#include <QColor>
#include <QStringList>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <stdio.h>
#include <autocompletion.h>

#include "Scintilla/scintilladoc.h"

extern void scan_string(const char* str);
class ScintillaDoc;

class RixLexer : public QsciLexerCustom
{
    Q_OBJECT

public:
    void setScintilladoc(ScintillaDoc *sd);
    void styleText(int start, int end);
    void styleToken(unsigned int length, int style);
    void styleError(unsigned int line, unsigned int offset, unsigned int length);
    void activateAutocomplete(std::string caller = "");
    void setWordChars(char *chars);
    void setErrorStyle(unsigned int indic, unsigned int style, unsigned int hexColour);
    QString description(int style) const;
    const char* language() const;
    const char* lexer() const;

private slots:
    void handleStyleNeeded(int pos);
    void handleCharAdded(int pos);
    void autoCompleteShortcut();

/*===============================================================================
FUNCTION:       Handle Found Errors

PROGRAMMER(S):  Tyler Trepanier-Bracken, Micah Willems

INTERFACE:      void handleFoundErrors()

NOTES:
Uses the global Error Array and highlights them according to their line,
column and number of characters afflicted.
===============================================================================*/
    void handleFoundErrors();

private:
    ScintillaDoc*   _scint;
};

#endif // RIXLEXER_H
