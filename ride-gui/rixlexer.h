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
    QString description(int style) const;
    const char* language() const;
    const char* lexer() const;

    const int      syntaxColors[14] = { 0,              // Unidentified token
                        (0 | (0 << 8) | (255 << 16)),   // Integer
                        (0 | (0 << 8) | (255 << 16)),   // Float
                        (0 | (0 << 8) | (255 << 16)),   // Int
                        (128 | (0 << 8) | (128 << 16)), // String
                        (128 | (0 << 8) | (128 << 16)), // Char
                        (0 | (0 << 8) | (0 << 16)),     // Class
                        (0 | (0 << 8) | (0 << 16)),     // Scope
                        (0 | (0 << 8) | (0 << 16)),     // Keyword
                        (0 | (0 << 8) | (0 << 16)),     // Return
                        (40 | (164 << 8) | (164 << 16)),// Identifier
                        (0 | (0 << 8) | (0 << 16)),     // Single-line comment
                        (0 | (0 << 8) | (0 << 16)),     // Multi-line comment (terminated)
                        (0 | (0 << 8) | (0 << 16))      // Multi-line comment (unterminated)
    };

private slots:
    void handleStyleNeeded(int pos);
    void handleCharAdded(int pos);
};

#endif // RIXLEXER_H
