#ifndef COMPILERHANDLER_H
#define COMPILERHANDLER_H

#include "globals.h"
#include "scintilladoc.h"

class CompilerHandler : public QObject
{
    Q_OBJECT
public:     // Public functions
    explicit CompilerHandler(QObject *parent);

    void compileRixFile(ScintillaDoc* doc = NULL);

    void readCompilerOutput(FILE* output, FILE* error);

private:    // Private functions

private:    // Private variables
    QString compile_begin;
    QString compile_end;

signals:
    void compilerOutput(const QString& line);
    void compilerError(const QString& error);

public slots:

};

#endif // COMPILERHANDLER_H
