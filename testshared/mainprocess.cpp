#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <stdio.h>


int main(int argc, char** argv) {
	int fd;
  fd = shm_open("/test", O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }
  ftruncate(fd, 10240);
  char *p = (char *)mmap(0, 10240, PROT_WRITE, MAP_SHARED, fd, 0);
  sprintf(p, "hello\n");	

	return 1;	
}
