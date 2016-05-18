#ifndef RIX_PARSER
#define RIX_PARSER

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../ride-parser/rixc.h"

/**
 * @brief      <p>This method is used to control all the mutex and condition. It
 *             only support one parse command at a time by acquire mutex, and
 *             then it monitor the condition until it's ready.</p>
 *
 * @param      err     an array list of error
 * @param      errnum  a number of error
 * @param[int] doc     the input stream aka the source code
 *
 * @return     0 success, -1 means there're errors
 *
 * @author     Duy Pham
 * @version    1.0
 */
int parseDocument(Error **err, int *errnum, const char *doc);



#endif