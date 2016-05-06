QT += widgets qml quick core gui
CONFIG      += debug qscintilla2
TARGET = RIDE
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp

RESOURCES += \
        qml.qrc \
        icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

#unix:!macx: LIBS += -L$$PWD/../QScintilla_gpl-2.9.2/Qt4Qt5/ -lqscintilla2

#INCLUDEPATH += $$PWD/../QScintilla_gpl-2.9.2/Qt4Qt5
#DEPENDPATH += $$PWD/../QScintilla_gpl-2.9.2/Qt4Qt5
