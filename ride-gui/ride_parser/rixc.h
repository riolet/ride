/* 
===============================================================================
SOURCE FILE:	rix.h 
					This files houses the defination of the rix compiler and 
					the rix parser. We only list the methods we created for the
					rix parser

PROGRAM:		Linux Terminal

FUNCTIONS:		int errorDetect(Error **, int *, const char *);
				void pushError(Error *e);
				void returnError();

PROGRAMMER(S):	Duy Pham, Phill Hood

NOTES:
===============================================================================
*/

#ifndef RITC_H
#define RITC_H

#include "ObjectTree.h"
#include "preproc.h"
#include "errors.h"
#include "ctype.h"

#define COMPILER_SEP "_$_"
#define GENERIC_PARAM "Generic_$$"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern Error **errors_array;

void defineRSLSymbols(Object *);

Object *findByName(char *name);
Object *findFunctionByFullName(char *name);

void handleEOF();

Object *completeExpression(Object *expression);
Object *finalize(Object *expression);
void closeBrace();
Object *makeReturn(Object *expression);
void checkPrevExists();
void incPrev();
void decPrev();

Object *beginClass(char *className, char *parentName, Object *typeArgs, bool isPrimitive);
void doneClass(Object *tree);
Object *beginFunction(char *returnType, char *funcName, Object *parameters);
void doneFunction(Object *tree);
Object *beginConstructor(Object *parameters);
void doneConstructor(Object *tree);
Object *beginDestructor(Object *parameters);
void doneDestructor(Object *tree);

void stdprintf(char *in);
void stdprintobj(Object *in);

Object *funcParameters(Object *tree, char *paramType, char *paramName);
Object *concatParams(Object *existing, Object *newParam);
Object *declareVariable(char *name, char *type);

Object *conjugateAssign(Object *subject, Object *verb, Object *objects);
Object *conjugate(Object *lhs, Object *verb, Object *rhs);
Object *conjugateConditional(Object *lhs, Object *verb, Object *rhs);
Object *injectC(char *code);

Object *verbAssignment(char *verb);
Object *verbMathOp(char *verb);
Object *verbComparison(char *verb);
Object *verbTernary();
Object *verbCondReturn();
Object *verbIdent(char *verb);
Object *verbDestructor();
Object *verbGetObjAtIdx();
Object *verbPutObjAtIdx();
Object *sVerbIdent(char *staticVerb);
Object *verbCtor(char *type, char *ytype);
Object *parenthesize(Object *expr);
Object *objectIdent(char *ident);
Object *objectNewIdent(char *ident);
Object *objectUnmarkedNewIdent(char *ident);
Object *objectSelfIdent(char *ident);
Object *objectfloat(float f);
Object *objectInt(int i);
Object *objectChar(char *c);
Object *objectPrev();
Object *objectPlaceHolderType(char *ident);
Object *objectString(char *string);
Object *conjugateAccessorIdent(Object *subject, char *field);

Object *createCodeBlock(Object *expression);

float simplifyfloat(float left, char *op, float right);
int simplifyInt(int left, char *op, int right);

/**
 * @brief      Parse a document text and detect error if it's existed
 *
 * @param      err     the array errors
 * @param      errnum  the number of errors
 * @param[in]  doc     the original document
 *
 * @return     0 for no error
 * 			   1 for error happens
 * @author     Phill Hood
 */
int errorDetect(Error **err, int *errnum, const char *doc);

/**
 * @brief      This is a callback method for error class. This method add an error into global error array and update the counter.
 *
 * @param      e     the error that is returned from the parser
 * @author     Phill Hood
 */
void pushError(Error *e);


/**
 * @brief      This is a callback method for error class. This method add an error into global error array and update the counter.
 *
 * @param      e     the error that is returned from the parser
 * @author     Duy Pham
 */
void returnError();

#endif
