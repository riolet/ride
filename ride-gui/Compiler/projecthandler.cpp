#include "projecthandler.h"


ProjectHandler::ProjectHandler()
{
    _directory = QDir::current();
    _isProject = false;
}

ProjectHandler::ProjectHandler(QString* filepath)
{
    _directory = QDir::current();
    _config = new QFile(*filepath);
    _isProject = false;

    bool result = false;


    result = loadProjectFile(_config);
}

bool ProjectHandler::isProject()
{
    return _isProject;
}

const QDir ProjectHandler::getDirectory() &
{
    return _directory;
}

bool ProjectHandler::loadProjectFile(QFile* file)
{
    QStringList keywords = createKeywords();

    if(!file->open(QFile::ReadOnly))
    {
        std::cerr << "Critical error, could not open default file." << std::endl;
        std::cerr << "Cannot use this file." << std::endl;
        return false;
    }

    QTextStream in(file);
    QString contents;
    bool result = false;
    contents = in.readAll();

    if(contents.isNull() || contents.isEmpty())
    {
        file->close();
        return false;
    }

    for(int index = 0; index < keywords.size(); index++)
    {
        int begin = contents.indexOf(keywords[index]);
        QString key_contents = contents.remove(0, begin - 1);

        if(keywords[index] == "[PROJECT_NAME]")
        {
            populateProjectName(&key_contents);
        }
        else if(keywords[index] == "[SOURCES]")
        {
            populateSources(&key_contents);
        }
        else if(keywords[index] == "[HEADERS]")
        {
            populateHeaders(&key_contents);
        }
        else if(keywords[index] == "[USER_PROFILE]")
        {
            populateUserProfile(&key_contents);
        }
        else if(keywords[index] == "[LIBS]")
        {
            populateLibs(&key_contents);
        }
    }

    if(!result)
    {
        // Handle project error here.
    }

    file->close();
    return true;

}

bool ProjectHandler::populateSources(QString* contents)
{

}

bool ProjectHandler::populateHeaders(QString* contents)
{

}

bool ProjectHandler::populateLibs(QString* contents)
{

}

bool ProjectHandler::populateUserProfile(QString *contents)
{

}

bool ProjectHandler::populateProjectName(QString* contents)
{

}

QStringList ProjectHandler::searchContents(QString* contents, QString start, QString key)
{
    QStringList foundList;
    QString line;
    QString word;
    QRegExp COMMENT("#");
    QRegExp MORE("\\");

    QTextStream in(contents);

    while (!in.atEnd())
    {
        line = in.readLine();

        // remove all comments from the line
        int size = line.length();
        int comment = line.indexOf(COMMENT);

        if(comment != -1)
        {
            line = line.remove(comment, size-comment);
            size = line.length();
        }

        if(line.isNull() || line.isEmpty())
            continue;
        else if(line.trimmed().length() == 0)
            continue;
        else if(line.contains(start))
            continue;

        // Found another "[Header]", stop processing
        else if(line.contains("["))
            return foundList;


        //
        // Process the line
        //
        QTextStream s(&line);

        bool more = true;
        bool firstTime = true;
        while(!s.atEnd() && (more || firstTime))
        {
            s >> word;
            int len = word.length();

            if(firstTime)
            {
                if(len == 1 && word.contains("\\"))
                {
                    more = true;
                    continue;
                }
            }

            if(len > 1 && word.contains(key))
            {
                foundList << word;

                // Search for a '\' character to indicate more
                //  source files.
                s >> word;
                if(word.length() == 1 && word.contains(MORE))
                {
                    more = true;
                }
                else
                {
                    more = false;
                }
            }
            firstTime = false;
        }

    }

    return foundList;
}



const QStringList ProjectHandler::createKeywords()
{
    QStringList keywords;
    keywords << "[SOURCES]" << "[HEADERS]" << "[USER_PROFILE]"
             << "[LIBS]" << "[PROJECT_NAME]";

    return keywords;
}
