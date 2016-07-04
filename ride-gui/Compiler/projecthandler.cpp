#include "projecthandler.h"


ProjectHandler::ProjectHandler()
{
    setDefaults();
}

ProjectHandler::ProjectHandler(QString* filepath)
{
    setDefaults();
    QFile* config = new QFile(*filepath);

    // Can't load the project properly
    if(loadProjectFile(config))
    {
        _config = config;
    }
    else
    {
        setDefaults();
    }


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
    QString contents = in.readAll();

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
            if(populateProjectName(&key_contents)) {continue;}
        }
        else if(keywords[index] == "[SOURCES]")
        {
            if(populateSources(&key_contents)) {continue;}
        }
        else if(keywords[index] == "[HEADERS]")
        {
            if(populateHeaders(&key_contents)) {continue;}
        }
        else if(keywords[index] == "[USER_PROFILE]")
        {
            if(populateUserProfile(&key_contents)) {continue;}
        }
        else if(keywords[index] == "[LIBS]")
        {
            if(populateLibs(&key_contents)) {continue;}
        }

        file->close();
        return false;
    }

    file->close();
    return true;

}

bool ProjectHandler::populateSources(QString* contents)
{
    QStringList tempList;
    QString key = ".rit";
    QString start = "[SOURCES]";

    tempList = searchContents(contents, key, start);
    if(tempList.size() == 0)
        return false;

    _sources = tempList;
    return true;
}

bool ProjectHandler::populateHeaders(QString* contents)
{
    QStringList tempList;
    QString key = ".rh";
    QString start = "[HEADERS]";

    tempList = searchContents(contents, key, start);
    if(tempList.size() == 0)
        return false;

    _headers = tempList;
    return true;
}

bool ProjectHandler::populateLibs(QString* contents)
{
    Q_UNUSED(contents)
    /* No libraries are supported yet.

    QStringList tempList;
    QString key = ".so";
    QString start = "[LIBS]";

    tempList = searchContents(contents, key, start);
    if(tempList.size() == 0)
        return false;

    _libs = tempList;
    return true;
    */
    return true;
}

bool ProjectHandler::populateUserProfile(QString *contents)
{
    QStringList tempList;
    QString key = ".cnf";
    QString start = "[USER_PROFILE]";

    tempList = searchContents(contents, key, start);
    if(tempList.size() == 1)
    {
        // Populate the themehandler here.
        _userprofile = new ThemeHandler(tempList[0]);
        //
        return true;
    }

    // Use the default profile, something went wrong.
    return false;
}

bool ProjectHandler::populateProjectName(QString* contents)
{
    QString name;
    QString start("[PROJECT_NAME]");

    name = searchProjectName(contents);
    if(name == NULL)
    {
        return false;
    }

    _project_name = name;
    return true;
}

QStringList ProjectHandler::searchContents(QString* contents, QString key, QString start, QString stop)
{
    Q_UNUSED(stop)

    QStringList foundList;
    QString line;
    QString word;
    QRegExp COMMENT("#");
    QRegExp MORE("\\");

    if(stop == NULL)
        stop = QString("[");

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
        else if(line.contains(stop))
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

QString ProjectHandler::searchProjectName(QString *contents)
{
    QStringList names;
    QString line;
    QString word;
    QRegExp COMMENT("#");
    QRegExp QUOTE("\\\"([\\w]|\\s)+\\\"");

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
        else if(line.contains("[PROJECT_NAME]"))
            continue;
        else if(line.contains("["))
            return NULL; // Return null string.

        int pos = QUOTE.indexIn(line);
        if (pos > -1)
        {
            word = QUOTE.cap();
            names << word;
        }

        if(names.size() > 1)
            return NULL;
        //
        // Process the line
        //
        /*QTextStream s(&line);
        while(!s.atEnd())
        {
            s >> word;
            if(word.count(QUOTE) == 2)
            {
                names << word;
            }

            if(names.size() > 1)
            {
                return NULL;
            }
        }*/
    }

    // Expected result that only one name with quotes is found.
    if(names.size() == 1)
    {
        return names[0];
    }

    return NULL;
}



const QStringList ProjectHandler::createKeywords()
{
    QStringList keywords;
    keywords << "[SOURCES]" << "[HEADERS]" << "[USER_PROFILE]"
             << "[LIBS]" << "[PROJECT_NAME]";

    return keywords;
}

void ProjectHandler::setDefaults()
{
    QStringList temp; // Empty List

    _userprofile    = new ThemeHandler();
    _sources        = temp;
    _headers        = temp;
    _libs           = temp;
    _project_name   = QString("New Project");
    _directory      = QDir::current();
    _isProject      = false;
}
