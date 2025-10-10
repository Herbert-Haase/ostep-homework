#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  // int fd;
  // if ((fd = open("./temp.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0) {
  //   perror("opening file failed");
  //   exit(1);
  // }
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    int num = printf("hello from child");
    if (fflush(stdout) == EOF) {
      perror("fflush failed");
    }
    // fprintf(stderr, "number of characters written:%d",num); // 16
  } else {
  }
  return 0;
}
