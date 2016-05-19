#include "rixparser_handler.h"
#include "rixparser.h"

Worker::Worker(struct error_object** err, int* err_num, char* doc) {
    _err 		= err;
    _err_num 	= err_num;
    _doc		= doc;
}

Worker::~Worker() { }

void Worker::process() {
    int *working;
    *working = 1;
    Initialize_error_detect_thread(_err, _err_num, _doc, working);
    emit finished();
}
