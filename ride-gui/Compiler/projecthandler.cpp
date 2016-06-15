#include "projecthandler.h"

ProjectHandler::ProjectHandler()
{
    _cur_dir = QDir::current();
    _isProject = false;
}

ProjectHandler::ProjectHandler(QString filepath)
{
    _cur_dir = QDir::current();
    _config = new QFile(filepath);

}

bool ProjectHandler::isProject()
{
    return _isProject;
}

bool ProjectHandler::loadProjectFile(QString filename)
{

}

bool ProjectHandler::populateSources(QString sources)
{

}

bool ProjectHandler::populateHeaders(QString headers)
{

}

bool ProjectHandler::populateLibs(QString libs)
{

}

bool ProjectHandler::populateUserProfile(QString config_filename)
{

}
