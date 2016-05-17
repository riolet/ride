#include "themehandler.h"

ThemeHandler::ThemeHandler(const QString &filepath)
{
    useDefault = true;

    _keylist << key_title << key_TEXT << key_INTEGER << key_FLOAT <<  key_STRING;
    _keylist << key_VERB << key_RET_TYPE << key_RET_ARROW << key_COMPARISON;
    _keylist << key_BOOLEAN << key_BITWISEOP << key_DEFAULT << key_BACKGROUND;
    _keylist << key_COMMENT << key_MCOMMENT;

    setToAbsoluteDefault();
    readDefaultFile();

    if(!filepath.isNull() && !filepath.isEmpty())
    {
        _file = new QFile(filepath);
        readFile(_file);

        useDefault = false;
    }

}

bool ThemeHandler::readDefaultFile()
{
    QDir curDir = QDir::current();
    curDir.cdUp();

    QFile default_config(curDir.path() + QString("/default.cnf"));

    if(!readFile(&default_config))
    {
        return false;
    }

    return true;
}

bool ThemeHandler::readFile(QFile *file)
{
    QStringList contents;

    if(!file->open(QFile::ReadOnly))
    {
        std::cerr << "Critical error, could not open default file." << std::endl;
        std::cerr << "Use internal theme." << std::endl;
        return false;
    }
    QTextStream in(file);

    QString line;
    while (!in.atEnd())
    {
        line = in.readLine();
        if(line.isNull() || line.isEmpty())
            continue;

        contents << line;
    }

    file->close();

    parseFileContents(contents);

    return true;
}

void ThemeHandler::parseFileContents(const QStringList &contents)
{
    int index = -1;

    // Need a better regular expression for matching strings.
    QRegExp match("\"");

    for(int i = 0; i < _keylist.size(); i++)
    {
        QString key = _keylist[i];
        QStringList result;
        int size;

        result = contents.filter(key);
        size = result.size();

        if(size == 0) // No lines contain this key
            continue;

        for(int i = 0; i < size; i++)
        {
            int j;
            QString input;
            QString line = result[i];

            index = line.indexOf(key) + (key.size());
            j = line.indexOf(match, index);

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
    QColor color;
    color.setNamedColor(input);

    if(!color.isValid()) // Improperly formatted hexcode string
    {
        color.setNamedColor(QString("#FFFFFF"));
    }

    if(key_title.contains(keyword))
    {
        _theme.title = input;
    }
    else if(key_TEXT.contains(keyword))
    {
        _theme.color_TEXT = color;
    }
    else if(key_COMMENT.contains(keyword))
    {
        _theme.color_COMMENT = color;
    }
    else if(key_MCOMMENT.contains(keyword))
    {
        _theme.color_MCOMMENT = color;
    }
    else if(key_INTEGER.contains(keyword))
    {
        _theme.color_INTEGER = color;
    }
    else if(key_FLOAT.contains(keyword))
    {
        _theme.color_FLOAT = color;
    }
    else if(key_STRING.contains(keyword))
    {
        _theme.color_STRING = color;
    }
    else if(key_VERB.contains(keyword))
    {
        _theme.color_VERB = color;
    }
    else if(key_RET_TYPE.contains(keyword))
    {
        _theme.color_RET_TYPE = color;
    }
    else if(key_RET_ARROW.contains(keyword))
    {
        _theme.color_RET_ARROW = color;
    }
    else if(key_COMPARISON.contains(keyword))
    {
        _theme.color_COMPARISON = color;
    }
    else if(key_BOOLEAN.contains(keyword))
    {
        _theme.color_BOOLEAN = color;
    }
    else if(key_BITWISEOP.contains(keyword))
    {
        _theme.color_BITWISEOP = color;
    }
    else if(key_DEFAULT.contains(keyword))
    {
        _theme.color_DEFAULT = color;
    }
    else if(key_BACKGROUND.contains(keyword))
    {
        _theme.color_BACKGROUND = color;
    }

}

void ThemeHandler::setToAbsoluteDefault()
{
    for(int i = 0; i < _keylist.size(); i++)
    {
        QString key = _keylist[i];
        assignColorString(key, QString("#FFFFFF"));
    }
}
