#ifndef SHAREDMEMORYUTILITIES_H
#define SHAREDMEMORYUTILITIES_H

#include "globals.h"

int RemapSharedMemory(struct semaphore_request* doc, struct semaphore_response* err, int newSize);


#endif // SHAREDMEMORYUTILITIES_H
