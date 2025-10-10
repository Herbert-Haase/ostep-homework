#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    char *myargs[3] = {"/bin/ls",NULL};
    execv(myargs[0], myargs);
  } else {
    wait(NULL);
  }
  return 0;
}
