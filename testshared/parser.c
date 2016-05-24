
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <stdio.h>


int main(int argc, char** argv) {
	int fd;
  char  word[1024];
  fd = shm_open("/test", O_RDWR, 0);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }
  char *p = (char *)mmap(0, 10240, PROT_READ, MAP_SHARED, fd, 0);
  sscanf(p, "%1023s", word);
  printf("%s", word);

	return 1;	
}
