QT += widgets core gui
CONFIG += debug
CONFIG += qscintilla2
TARGET = RIDE
TEMPLATE = app
LIBS += -lfl
LIBS += -lrt
LIBS += -lpthread

HEADERS += \
    mainwindow.h \
    Scintilla/scintilladoc.h \
    globals.h \
    aboutdialog.h \
    Scintilla/themehandler.h \
    Compiler/compilerhandler.h \
    rixlexer.h \
    lexershare.h \
    syntaxcolours.h \
    autocompletion.h \
    sharedmemoryutilities.h \
    Compiler/projecthandler.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Scintilla/scintilladoc.cpp \
    aboutdialog.cpp \
    Compiler/compilerhandler.cpp \
    rixlexer.cpp \
    Scintilla/themehandler.cpp \
    autocompletion.cpp \
    sharedmemoryutilties.cpp \
    Compiler/projecthandler.cpp

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

DISTFILES += \
    flex_todo.txt

# Copy ride_parser from source to build folder
copydata.commands = $(COPY_DIR) $$PWD/ride_parser $$OUT_PWD/ride_parser
parsermake.commands =
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
