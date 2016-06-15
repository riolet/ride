#ifndef PROJECTHANDLER_H
#define PROJECTHANDLER_H

#include "Scintilla/scintilladoc.h"
#include "Scintilla/themehandler.h"
#include "QStringList"

class ProjectHandler
{
public: // Public methods
    ProjectHandler();
    ProjectHandler(QString filepath);
    bool isProject();

private: // Private methods
    bool loadProjectFile(QString filename);
    bool populateSources(QString sources);
    bool populateHeaders(QString headers);
    bool populateLibs(QString libs);
    bool populateUserProfile(QString config_filename);

public: // public variables
    ThemeHandler    _userprofile;
    QStringList     _sources;
    QStringList     _headers;
    QStringList     _libs;
    QString         _project_name;

private: // private variables
    QFile*          _config;
    QDir            _cur_dir;
    bool            _isProject;

};

#endif // PROJECTHANDLER_H
