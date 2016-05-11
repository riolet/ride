#include "themehandler.h"

ThemeHandler::ThemeHandler(const QString &filepath)
{
    _keylist << key_title << key_TEXT << key_INTEGER << key_FLOAT <<  key_STRING;
    _keylist << key_VERB << key_RET_TYPE << key_RET_ARROW << key_COMPARISON;
    _keylist << key_BOOLEAN << key_BITWISEOP << key_DEFAULT << key_BACKGROUND;
    _keylist << key_COMMENT << key_MCOMMENT;

    if(!readDefaultFile())
    {
        // TODO: Handle
    }

    /*
    _file = new QFile(filepath);
    if (!_file->open(QFile::ReadOnly))
    {
        useDefault = true;
    }
    else
    {
        _stream = new QTextStream(_file);
        useDefault = false;
    }
    */

}

bool ThemeHandler::readDefaultFile()
{
    QDir curDir = QDir::current();
    curDir.cdUp();
    QStringList contents;

    QFile       default_config(curDir.path() + QString("/default.cnf"));
    if(!default_config.open(QFile::ReadOnly))
    {
        std::cerr << "Critical error, could not open default file." << std::endl;
        std::cerr << "Use internal theme." << std::endl;
        return false;
    }
    QTextStream in(&default_config);

    QString line;
    while (!in.atEnd())
    {
        line = in.readLine();
        if(line.isNull() || line.isEmpty())
            continue;

        contents << line;
    }

    parseFileContents(contents);

    return true;
}

void ThemeHandler::parseFileContents(const QStringList &contents)
{
    int index = -1;
    QRegExp match("\"");
    for(const QString key : _keylist)
    {
        QStringList result;
        int size;

        result = contents.filter(key);
        size = result.size();

        if(size == 0)
            continue;

        for(int i = 0; i < size; i++)
        {
            int j;
            QString input;
            QString line = result[i];

            index = line.indexOf(key) + (key.size() - 1);
            j = line.indexOf(match, key.size());

            if(j++ == -1)
                continue;

            while(j < line.size())
            {
                if(line[j] == '\"')
                    break;

                input.append(line[j]);
                j++;
            }
            assignColorString(key, input);
        }

    }
}

void ThemeHandler::assignColorString(const QString &keyword, const QString &input)
{
    //TODO: Parse the input into a QColor
    //QColor color = input.Turn_Into_Color
    if(key_title.contains(keyword))
    {
        _theme.title = input;
    }
    else if(key_TEXT.contains(keyword))
    {
        _theme.color_TEXT = input;
    }
    else if(key_COMMENT.contains(keyword))
    {
        _theme.color_COMMENT = input;
    }
    else if(key_MCOMMENT.contains(keyword))
    {
        _theme.color_MCOMMENT = input;
    }
    else if(key_INTEGER.contains(keyword))
    {
        _theme.color_INTEGER = input;
    }
    else if(key_FLOAT.contains(keyword))
    {
        _theme.color_FLOAT = input;
    }
    else if(key_STRING.contains(keyword))
    {
        _theme.color_STRING = input;
    }
    else if(key_VERB.contains(keyword))
    {
        _theme.color_VERB = input;
    }
    else if(key_RET_TYPE.contains(keyword))
    {
        _theme.color_RET_TYPE = input;
    }
    else if(key_RET_ARROW.contains(keyword))
    {
        _theme.color_RET_ARROW = input;
    }
    else if(key_COMPARISON.contains(keyword))
    {
        _theme.color_COMPARISON = input;
    }
    else if(key_BOOLEAN.contains(keyword))
    {
        _theme.color_BOOLEAN = input;
    }
    else if(key_BITWISEOP.contains(keyword))
    {
        _theme.color_BITWISEOP = input;
    }
    else if(key_DEFAULT.contains(keyword))
    {
        _theme.color_DEFAULT = input;
    }
    else if(key_BACKGROUND.contains(keyword))
    {
        _theme.color_BACKGROUND = input;
    }

}
