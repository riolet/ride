#ifndef SHAREDMEMORYUTILITIES_H
#define SHAREDMEMORYUTILITIES_H

#include "globals.h"
int InitializeSharedMemory(struct semaphore_request* doc, struct semaphore_response* err);
int CreateSharedMemory(struct semaphore_request* doc, struct semaphore_response* err);
int CreateSemaphores(struct semaphore_request* doc, struct semaphore_response* err);

int RemapSharedMemory(struct semaphore_request* doc, struct semaphore_response* err, int newSize);

void CleanUpSharedMemory(struct semaphore_request* doc, struct semaphore_response* err);
void DeleteSharedMemory(struct semaphore_request* doc, struct semaphore_response* err);
void RemoveSemaphores();


#endif // SHAREDMEMORYUTILITIES_H
