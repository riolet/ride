#include "rixparser.h"
#include "rixparser_handler.h"
#include "ride_parser/rixc.h"

int Initialize_error_detect_thread(struct error_object** err, int* err_num, char* doc)
{
	QThread* thread = new QThread;
	Worker* worker = new Worker(err, err_num, doc);
	worker->moveToThread(thread);
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
	connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
	connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
    return 1;
}

Worker::Worker(struct error_object** err, int* err_num, char* doc) { 
	_err 		= err;
	_err_num 	= err_num;
	_doc		= doc;
}
 
Worker::~Worker() { }
 
void Worker::process() {
	int *working;
	*working = 1;
	errorDetect(_err, _err_num, _doc, working);
    emit finished();
}
