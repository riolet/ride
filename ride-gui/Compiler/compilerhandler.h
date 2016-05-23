/*===============================================================================
HEADER FILE:	compilerhandler.h 
					Class dedicated to handling the compiler and running the
					"rix" shell script that is found inside of your rix folder.

PROGRAM:		Ride

FUNCTIONS:		explicit CompilerHandler(QObject *parent);
                bool compileRixFile(ScintillaDoc* doc = NULL);
    			void readCompilerOutput(FILE* output, FILE* error);

QT SIGNALS:    	void compilerOutput(const QString& line);
    			void compilerError(const QString& error);

PROGRAMMER(S):	Tyler Trepanier-Bracken

NOTES:
This header file declares all of the functions that are defined inside of the
compilerhandler.cpp file. This class runs the "rix" shell script and sends all
compilation messages to the mainwindow. This is done via signals which are
caught by the mainwindow slot.
===============================================================================*/
#ifndef COMPILERHANDLER_H
#define COMPILERHANDLER_H

#include "globals.h"
#include "Scintilla/scintilladoc.h"

class CompilerHandler : public QObject
{
    Q_OBJECT
public:     // Public functions
    
    //Only this version of the constructor is allowed.
    explicit CompilerHandler(QObject *parent);

/*===============================================================================
FUNCTION: 		Compile Rix File

PROGRAMMER(S):	Tyler Trepanier-Bracken

INTERFACE:		bool compileRixFile(ScintillaDoc* doc = NULL)

PARAMETERS:		ScintillaDoc* doc
					Document that will have its contents compiled and executed.

RETURNS:        -TRUE   : Able to run the compiler.
                -FALSE  : Unable to run the compiler.

NOTES:
Creates a child process to carry out the rix file compilation and reads in the
newly creating compilation messages.
===============================================================================*/
    bool compileRixFile(ScintillaDoc* doc = NULL);

/*===============================================================================
FUNCTION: 		Read Compiler Output

PROGRAMMER(S):	Tyler Trepanier-Bracken

INTERFACE:		void readCompilerOutput(FILE* output, FILE* error)

PARAMETERS:		FILE* output 
					Output file that contains all standard output messages.
				FILE* error 
					Error file that contains all standard error messages.

RETURNS:		Void

NOTES:
This function takes in the output file and error file and waits until the
system call for the Rix compilation finishes by detecting the "...END..."
in the output file. Afterwards, it will send all output and errors via the
compilerOutput and compilerError signals. 
===============================================================================*/
    void readCompilerOutput(FILE* output, FILE* error);

private:    // Private functions

private:    // Private variables

// QString constant to indicate that compilation has begun.
    QString compile_begin; 

// QString constant to indicate the end of the compilation.
    QString compile_end;

signals:

/*===============================================================================
QT SIGNAL: 		Compiler Output

PROGRAMMER(S):	Tyler Trepanier-Bracken

INTERFACE:		void compilerOutput(const QString& line)

PARAMETERS:		const QString& line
					Line of standard output message. 

RETURNS:		Void

NOTES:
Signal to be caught by another QObject for standard output messages.
===============================================================================*/
    void compilerOutput(const QString& line);

/*===============================================================================
QT SIGNAL: 		Compiler Error

PROGRAMMER(S):	Tyler Trepanier-Bracken

INTERFACE:		void compilerOutput(const QString& error)

PARAMETERS:		const QString& error
					Line of standard output message. 

RETURNS:		Void

NOTES:
Signal to be caught by another QObject for standard error messages.
===============================================================================*/
    void compilerError(const QString& error);

public slots:

};

#endif // COMPILERHANDLER_H
