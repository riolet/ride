#include "themehandler.h"

ThemeHandler::ThemeHandler(const QString &filepath)
{
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
}

bool ThemeHandler::readDefaultFile()
{
    QDir curDir = QDir::current();
    curDir.cdUp();

    QFile       default_config(curDir.path() + QString("/default.cnf"));
    QTextStream in(&default_config);

    QString line;
    while (!in.atEnd())
    {
        line = in.readLine();
        if(line.isNull() || line.isEmpty())
            continue;

        parseLine(line);
    }
}

void ThemeHandler::parseLine(const QString &line)
{

    //line.indexOf(y)
}

