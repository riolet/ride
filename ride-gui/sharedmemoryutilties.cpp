#include "sharedmemoryutilities.h"

int InitializeSharedMemory(struct semaphore_request* doc, struct semaphore_response* err)
{
    shm_unlink(SHARED_CODE);
    shm_unlink(SHARED_ERROR);
    shm_unlink(SHARED_NUMBER_ERROR);
    sem_unlink(SEM_CODE);
    sem_unlink(SEM_ERROR);

    if(CreateSemaphores(doc, err) == -1)
        return -1;

    if(CreateSharedMemory(doc, err) == -1)
        return -1;

    return 0;
}

int CreateSemaphores(struct semaphore_request* doc, struct semaphore_response* err)
{
    int sem_val = 0;

    // Create semaphore
    (*doc).sem = sem_open(SEM_CODE,  O_CREAT, 0600, 0);
    (*err).sem = sem_open(SEM_ERROR, O_CREAT, 0600, 0);

    if ((*doc).sem == SEM_FAILED || (*err).sem == SEM_FAILED)
    {
        perror("Semphore creation");
        return -1;
    }

    // Note: Use this ONLY for a HARD reset, you can easily screw up expected behaviour here.
    do // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_getvalue((*doc).sem, &sem_val);
        if(sem_val < 0)
        {
            sem_post((*doc).sem);
        }
        else if(sem_val > 0)
        {
            sem_wait((*doc).sem);
        }

    }
    while(sem_val != 0);

    do // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_getvalue((*err).sem, &sem_val);
        if(sem_val < 0)
        {
            sem_post((*err).sem);
        }
        else if(sem_val > 0)
        {
            sem_wait((*err).sem);
        }

    }
    while(sem_val != 0);

    return 0;
}

int CreateSharedMemory(struct semaphore_request* doc, struct semaphore_response* err)
{
    // Initialize file descriptor
    (*doc).fd            = shm_open(SHARED_CODE,  O_RDWR | O_CREAT | O_TRUNC, 0666);
    (*err).fd            = shm_open(SHARED_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);
    (*err).fd_num_err    = shm_open(SHARED_NUMBER_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if ((*doc).fd == -1 || (*err).fd == -1 || (*err).fd_num_err == -1)
    {
        perror("Shared memory creation");
        return -1;
    }

    //Manipulate file descriptor size
    (*doc).max_size = 10240;
    (*err).max_size = 10240;

    if(ftruncate((*doc).fd,         (*doc).max_size) == -1 ||
       ftruncate((*err).fd,         (*err).max_size) == -1 ||
       ftruncate((*err).fd_num_err, sizeof(int))     == -1)
    {
        perror("Could not allocate shared memory resources.");
        return -1;
    }

    // Map content with descriptor
    (*doc).content      = (char *)mmap(0, (*doc).max_size, PROT_WRITE, MAP_SHARED, (*doc).fd,         0);
    (*err).content      = (char *)mmap(0, (*err).max_size, PROT_READ,  MAP_SHARED, (*err).fd,         0);
    (*err).errNumber    = (int*)  mmap(0, sizeof(int),     PROT_READ,  MAP_SHARED, (*err).fd_num_err, 0);

    if((*doc).content == MAP_FAILED || (*err).content == MAP_FAILED || (*err).errNumber == MAP_FAILED)
    {
        perror("Memory map");
        return -1;
    }

    return 0;
}

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

    return newSize;
}

void CleanUpSharedMemory(struct semaphore_request* doc, struct semaphore_response* err)
{
    DeleteSharedMemory(doc, err);
    RemoveSemaphores();
}

void DeleteSharedMemory(struct semaphore_request* doc, struct semaphore_response* err)
{
    ftruncate((*doc).fd,           0);
    ftruncate((*err).fd,         0);
    //ftruncate((*err).fd_num_err, 0);

    shm_unlink(SHARED_CODE);
    shm_unlink(SHARED_ERROR);
    shm_unlink(SHARED_NUMBER_ERROR);

    munmap((*err).content, (*err).max_size);
    munmap((*doc).content, (*err).max_size);
}

void RemoveSemaphores()
{
    sem_unlink(SEM_CODE);
    sem_unlink(SEM_ERROR);
}
