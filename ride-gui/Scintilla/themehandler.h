/*===============================================================================
HEADER FILE:    themehandler.h 
                    Class dedicated to handling the colouring scheme of the 
                    scintilla document in regards to variables, integers, etc.

PROGRAM:        Ride

FUNCTIONS:      explicit ThemeHandler(QWidget *parent = 0);
                bool readDefaultFile();
                bool readFile(QFile* file);
                void parseFileContents(const QStringList &contents);
                void assignColorString(const QString &keyword, const QString &input);
                void setToAbsoluteDefault();

QT SIGNALS:     void textChanged();

PROGRAMMER(S):  Tyler Trepanier-Bracken

NOTES:
This theme handler first reads in the default configuration file and allows
the user to change the colour theme. 

THIS CLASS IS CURRENTLY UNFINISHED BUT STILL PARSES THE CONFIG FILE CORRECTLY.
Requires:
-changing rix lexer colours using this class
===============================================================================*/

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
    
    // Do not use any other constructor aside from this one.
    explicit ThemeHandler(const QString &filepath = QString(""));

private:    // Private functions

/*===============================================================================
FUNCTION:       Read Default File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool readDefaultFile()

RETURNS:        -TRUE   : Able to read the default configuration file.
                -FALSE  : Unable to read the default configuration file. 

NOTES:
Attempts to read in the hardcoded default configuration file and using that
file, sets the theme's colours based on that files configuration.
===============================================================================*/
    bool readDefaultFile();

/*===============================================================================
FUNCTION:       Read File

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      bool readFile(QFile* file);

PARAMETERS:     QFile* file
                    File that will be attempted to be opened.

RETURNS:        -TRUE   : Read the contents of a file and placed the gathered
                          information into its key/value slot.
                -FALSE  : Unable open the file for reading. 

NOTES:
Read the contents of a file and placed the gathered information into its 
key/value slot. 
===============================================================================*/    
    bool readFile(QFile* file);

/*===============================================================================
FUNCTION:       Parse File Contents

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void parseFileContents(const QStringList &contents)

PARAMETERS:     const QStringList &contents
                    An opened file's contents split by a newline character.

RETURNS:        Void

NOTES:
Goes through a list of strings (from an opened file) and assigns every valid
key with its color. Any errors will not overwrite the currently existing key
colour (defaults to white).
===============================================================================*/
    void parseFileContents(const QStringList &contents);

/*===============================================================================
FUNCTION:       Assign Color String

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void assignColorString(const QString &keyword, const QString &input)

PARAMETERS:     const QString &keyword 
                    Keyword of the color string.
                const QString &input
                    Configuration file input string

RETURNS:        Void

NOTES:
Assigns the theme's colour to according to it key. All errors will result in a
reassignment of the key being white.
===============================================================================*/
    void assignColorString(const QString &keyword, const QString &input);

/*===============================================================================
FUNCTION:       Set To Absolute Default

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void setToAbsoluteDefault()

RETURNS:        Void

NOTES:
Sets every colour in the theme to be white.  
===============================================================================*/
    void setToAbsoluteDefault();

private:    // Private variables
    QFile*                  _file;      // Current configuration file.
    QTextStream*            _stream;    // Used for reading the config file's contents
    QStringList             _keylist;   // List of constant keys using for parsing.
    Theme                   _theme;     // Current theme selected and its colours.
    bool                    useDefault; // Use default theme flag.

    // Key values for reading a configuration file and parsing the file.
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
