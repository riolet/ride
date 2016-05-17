#ifndef GLOBALS_H
#define GLOBALS_H

#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <vector>
#include <QFont>
#include <Qsci/qsciscintilla.h>
#include <QDebug>

#ifndef RIXCOMPILER
#define RIXCOMPILER
extern int e_count;
extern int g_lineNum;
extern int g_lineCol;
extern int g_headerLines;

#include "../ride_parser/rixc.h"    // NEED TO LINK RIDE TO RIDE_PARSER
#include "../ride_parser/errors.h"
#include "../ride_parser/ObjectTree.h"
#include "../ride_parser/preproc.h"

#endif

#endif // GLOBALS_H
