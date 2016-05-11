#ifndef THEMEHANDLER_H
#define THEMEHANDLER_H
#include <QTextStream>
#include <QColor>
#include "globals.h"

struct Theme{
    QString title;
    QColor TEXT;
    QColor INTEGER;
    QColor FLOAT;
    QColor STRING;
    QColor VERB;
    QColor RET_TYPE;
    QColor RET_ARROW;
    QColor COMPARISON;
    QColor BOOLEAN;
    QColor BITWISEOP;
    QColor DEFAULT;
    QColor BACKGROUND;
};

class ThemeHandler
{

public:     //Public functions
    explicit ThemeHandler(const QString &filepath = QString(""));

private:    // Private functions
    bool readDefaultFile();
    void parseLine(const QString& line);

private:    // Private variables
     QFile*         _file;
     QTextStream*   _stream;
     Theme          _theme;
     bool           useDefault;

    /*enum theme_keywords
    {
     TITLE       = "Default Theme",
     DEFAULT     = "\"default\"",
     INTEGER     = "\"integer\"",
     FLOAT       = "\"float\"",
     STRING      = "\"string\"",
     VERB        = "\"verb\"",
     RET_TYPE    = "\"ret_type\"",
     RET_ARROW   = "\"ret_arrow\"",
     COMPARISON  = "\"comparison\"",
     BOOLEAN     = "\"boolean\"",
     BITWISEOP   = "\"bitwiseop\"",
     BACKGROUND  = "\"background\""
    };*/
};

#endif // THEMEHANDLER_H
