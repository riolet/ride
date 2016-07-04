#ifndef PROJECTHANDLER_H
#define PROJECTHANDLER_H

#include "Scintilla/scintilladoc.h"
#include "Scintilla/themehandler.h"
#include "QStringList"

class ProjectHandler
{
public: // Public methods
    ProjectHandler();
    ProjectHandler(QString* filepath);
    bool isProject();
    const QDir getDirectory() &;

private: // Private methods
    bool loadProjectFile(QFile* file);
    bool populateSources(QString* contents);
    bool populateHeaders(QString* contents);
    bool populateLibs(QString* contents);
    bool populateUserProfile(QString* contents);
    bool populateProjectName(QString* contents);
    QStringList searchContents(QString* contents, QString key, QString start, QString stop = NULL);
    QString searchProjectName(QString* contents);
    const QStringList createKeywords();
    void setDefaults();

public: // public variables
    ThemeHandler*   _userprofile;
    QStringList     _sources;
    QStringList     _headers;
    QStringList     _libs;
    QString         _project_name;
    QDir            _directory;

private: // private variables
    QFile*          _config;
    bool            _isProject;
};

#endif // PROJECTHANDLER_H
