#ifndef THEMEHANDLER_H
#define THEMEHANDLER_H
#include <QTextStream>
#include <QColor>
#include "globals.h"

struct Theme
{
    QString title;
    QColor color_TEXT;
    QColor color_INTEGER;
    QColor color_COMMENT;
    QColor color_MCOMMENT;
    QColor color_FLOAT;
    QColor color_STRING;
    QColor color_VERB;
    QColor color_RET_TYPE;
    QColor color_RET_ARROW;
    QColor color_COMPARISON;
    QColor color_BOOLEAN;
    QColor color_BITWISEOP;
    QColor color_DEFAULT;
    QColor color_BACKGROUND;
};

class ThemeHandler
{

public:     //Public functions
    explicit ThemeHandler(const QString &filepath = QString(""));

private:    // Private functions
    bool readDefaultFile();
    bool readFile(QFile* file);
    void parseFileContents(const QStringList &contents);
    void assignColorString(const QString &keyword, const QString &input);
    void setToAbsoluteDefault();

private:    // Private variables
    QFile*                  _file;
    QTextStream*            _stream;
    QStringList             _keylist;
    Theme                   _theme;
    bool                    useDefault;

    const QString key_title       = QString("\"title\"");
    const QString key_TEXT        = QString("\"text\"");
    const QString key_INTEGER     = QString("\"integer\"");
    const QString key_COMMENT     = QString("\"comment\"");
    const QString key_MCOMMENT    = QString("\"mcomment\"");
    const QString key_FLOAT       = QString("\"float\"");
    const QString key_STRING      = QString("\"string\"");
    const QString key_VERB        = QString("\"verb\"");
    const QString key_RET_TYPE    = QString("\"ret_type\"");
    const QString key_RET_ARROW   = QString("\"ret_arrow\"");
    const QString key_COMPARISON  = QString("\"comparison\"");
    const QString key_BOOLEAN     = QString("\"boolean\"");
    const QString key_BITWISEOP   = QString("\"bitwiseop\"");
    const QString key_DEFAULT     = QString("\"default\"");
    const QString key_BACKGROUND  = QString("\"background\"");
};

/*
    #DEFAULT THEME COLOUR FOR RIDE
    "title":"Default",
    "default":"#FFFFFF",
    "text":"#FFFFFF",
    "comment":"#28551D",
    "mcomment":"#28991D",
    "integer":"#CC00FF",
    "float":"#CC00FF",
    "string":"#E88A0C",
    "verb":"#2AFFED",
    "ret_type":"#FF19D3",
    "ret_arrow":"#FF19D3",
    "comparison":"#FFFFFF",
    "boolean":"#CC00FF",
    "bitwiseop":"#0C1A99",
    "background":"#666666"
*/

#endif // THEMEHANDLER_H
