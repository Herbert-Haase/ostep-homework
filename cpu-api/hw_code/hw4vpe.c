#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char** environ;

int main(void) {
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    char *myargs[3];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = NULL;
    execvpe(myargs[0], myargs, environ);
  } else {
    wait(NULL);
  }
  return 0;
}
