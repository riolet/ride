#ifndef SCINTILLADOC_H
#define SCINTILLADOC_H
#include <QObject>
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>
#include "globals.h"

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

private: // Private functions
    void setWrapMode(bool enable);

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

};

#endif // SCINTILLADOC_H

