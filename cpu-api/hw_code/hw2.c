#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
  int fd;
  if ((fd = open("./temp.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0) {
    perror("opening file failed");
    exit(1);
  }
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if(rc == 0){
  char buf[] = "child ";
  size_t nbytes = sizeof buf;
  write(fd, buf, nbytes);

  } else {
  char buf[] = "parent ";
  size_t nbytes = sizeof buf;
  write(fd, buf, nbytes);
  }
  close(fd);
  return 0;
}
