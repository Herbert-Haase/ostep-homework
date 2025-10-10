#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    execl("/bin/ls", "ls", (char *)NULL);
  } else {
    wait(NULL);
  }
  return 0;
}
