QT += widgets core gui
CONFIG      += debug qscintilla2
TARGET = RIDE
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scintilladoc.cpp \
    aboutdialog.cpp \
    themehandler.cpp \
    compilerhandler.cpp \
    rixlexer.cpp \
    themehandler.cpp 

RESOURCES += \
        icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui \
    aboutdialog.ui

HEADERS += \
    mainwindow.h \
    scintilladoc.h \
    globals.h \
    aboutdialog.h \
    themehandler.h \
    compilerhandler.h \
    rixlexer.h \
    themehandler.h
