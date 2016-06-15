#include "sharedmemoryutilities.h"


/*===============================================================================
FUNCTION:   Remap Shared Memory

PROGRAMMER: Tyler Trepanier-Bracken

INTERFACE:  int RemapSharedMemory(struct semaphore_request* doc,
                                  struct semaphore_response* err,
                                  int newSize)

RETURNS:    >>  0 upon successful remapping of the shared memory segment
            >> -1 when there was an issue reassigning memory with the shared
                    memory segment.

NOTES:
Reallocates the shared memory to a different size value.
===============================================================================*/
int RemapSharedMemory(struct semaphore_request* doc, struct semaphore_response* err, int newSize)
{
    if(munmap((*doc).content, (*doc).max_size) == -1
            || munmap((*err).content, (*err).max_size) == -1)
    {
        std::cerr << "Could not unmap the shared memory." << std::endl;
        return -1;
    }

    if(ftruncate((*doc).fd, newSize) == -1
            || ftruncate((*err).fd, newSize) == -1)
    {
        std::cerr << "Could not increase the file size" << std::endl;
        return -1;
    }

    (*doc).content = (char *) mmap(0, newSize, PROT_WRITE, MAP_SHARED, (*doc).fd, 0);
    (*err).content = (char *) mmap(0, newSize, PROT_READ,  MAP_SHARED, (*err).fd, 0);

    if((*doc).content == MAP_FAILED || (*err).content == MAP_FAILED)
    {
        std::cerr << "Unable to remap the shared memory" << std::endl;
        return -1;
    }

    (*doc).max_size = (*err).max_size = newSize;

    return 0;
}
