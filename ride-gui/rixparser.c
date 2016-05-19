#include "rixparser.h"
#include "rixparser_handler.h"

int Initialize_error_detect_thread(struct error_object** err, int* err_num, char* doc)
{
    errorDetect(err, err_num, doc);
}
