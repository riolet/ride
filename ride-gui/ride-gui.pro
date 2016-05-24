QT += widgets core gui
CONFIG += debug
CONFIG += qscintilla2
TARGET = RIDE
TEMPLATE = app
LIBS += -lfl
LIBS += -lrt
LIBS += -lpthread
#DEPENDPATH += ../
#INCLUDEPATH += ../
#LIBS += ../libqscintilla2.so

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Scintilla/scintilladoc.cpp \
    aboutdialog.cpp \
    Compiler/compilerhandler.cpp \
    rixlexer.cpp \
    Scintilla/themehandler.cpp

FLEXSOURCES = lex.l

OTHER_FILES += \
    $$FLEXSOURCES

RESOURCES += \
        icons.qrc

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui \
    aboutdialog.ui

HEADERS += \
    mainwindow.h \
    Scintilla/scintilladoc.h \
    globals.h \
    aboutdialog.h \
    Scintilla/themehandler.h \
    Compiler/compilerhandler.h \
    rixlexer.h \
    lexershare.h \
    syntaxcolours.h

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
