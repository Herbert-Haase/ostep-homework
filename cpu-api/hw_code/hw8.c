#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BSIZE 100

int main(void) {
  int fildes[2];
  size_t buf_s = BSIZE;
  char buf[BSIZE];
  ssize_t nbytes;

  if (pipe(fildes) < 0) {
    perror("pipe failed");
    exit(1);
  }
  int child1 = fork();
  if (child1 < 0) {
    perror("fork failed");
  } else if (child1 == 0) {
    // convert PID to string
    char pid[buf_s];
    sprintf(pid, "_id%d\n", getpid());
    pid[strlen(pid) + 1] = '\0';
    strcpy(buf, "hi from child");
    strcat(buf, pid);
    // write to pipe
    close(fildes[0]);
    if (write(fildes[1], buf, buf_s) < 0) {
      perror("Writing to pipe failed");
      exit(1);
    }
    close(fildes[1]);
    exit(EXIT_SUCCESS);
  }

  int child2 = fork();
  if (child2 < 0) {
    perror("fork failed");
  } else if (child2 == 0) {
    close(fildes[1]);
    int read_s = read(fildes[0], buf, buf_s);
    if (read_s < 0) {
      perror("Reading from pipe failed");
      exit(1);
    }
    buf[read_s] = '\0';
    close(fildes[0]);
    printf("%s", buf);
    exit(EXIT_SUCCESS);
  }

  close(fildes[0]);
  close(fildes[1]);
  waitpid(child1, NULL, 0);
  waitpid(child2, NULL, 0);
  return 0;
}
