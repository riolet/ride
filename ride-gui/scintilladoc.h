#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QObject>
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>
#include "globals.h"
#include "lexershare.h"

#define ZOOM_FACTOR 2
#define MARGIN_WIDTH QString("123456")

class ScintillaDoc : public QObject
{
    Q_OBJECT
public:
    explicit ScintillaDoc(QObject *parent = 0);

    bool loadFile(QString filepath);

    bool saveFile(QString newFilePath = QString(""));

    bool saveAs(QString filepath);

    void clearTextArea();

    bool isBlank();

    bool isModified();

    void zoom_in();

    void zoom_out();

    void gotoLine(int line);

    int getTotalLines();

    const QString getAllText();

    void parseError();

private: // Private functions
    void setWrapMode(bool enable);

    void handleFoundErrors(); //incomplete function

signals:
    void textChanged();

private slots:

    // Stops signals from being sent too many times.
    void scintillaTextChanged();

public: // public variables
    QsciScintilla*  _editText;
    QString         _filename;
    QString         _filepath;
    QString         _errorString;
    QFile*          _file;

private: // private variables
    bool            _isBlank;
    bool            _modified;
    enum            syntaxTypes {
                        tInteger    = 1,
                        tFloat      = 2,
                        tInt        = 3,
                        tString     = 4,
                        tChar       = 5,
                        tClass      = 6,
                        tScope      = 7,
                        tKeyword    = 8,
                        tReturn     = 9,
                        tIdentifier = 10,
                        tSingleComm = 11,
                        tMultiComm  = 12,
                        tMultiCommUnterm = 13
    };
    int            syntaxColors[14] = { 0,              // Unidentified token
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
};

#endif // SCINTILLADOC_H

