QT += widgets core gui
CONFIG += debug
CONFIG += qscintilla2
TARGET = RIDE
TEMPLATE = app
LIBS += -lfl
#DEPENDPATH += ../
#INCLUDEPATH += ../
#LIBS += ../libqscintilla2.so

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scintilladoc.cpp \
    aboutdialog.cpp \
    compilerhandler.cpp \
    rixlexer.cpp \
    themehandler.cpp \
    rixparser.c

FLEXSOURCES = lex.l

OTHER_FILES += \
    $$FLEXSOURCES

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
    lexershare.h \
    rixparser.h \
    ride_parser/rixc.h

flexsource.input = FLEXSOURCES
flexsource.output = ${QMAKE_FILE_BASE}.cpp
flexsource.commands = flex --header-file=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.cpp ${QMAKE_FILE_IN}
flexsource.variable_out = SOURCES
flexsource.name = Flex Sources ${QMAKE_FILE_IN}
flexsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += flexsource

flexheader.input = FLEXSOURCES
flexheader.output = ${QMAKE_FILE_BASE}.h
flexheader.commands = @true
flexheader.variable_out = HEADERS
flexheader.name = Flex Headers ${QMAKE_FILE_IN}
flexheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += flexheader
