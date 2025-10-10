#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void) {
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    int rc_wait = wait(NULL);
    printf("child_id:%d, wait is:%d\n",getpid(),rc_wait); // -1 because no child
  } else {
    int rc_wait = wait(NULL);
    printf("parent_id:%d, wait is:%d\n",getpid(),rc_wait);
  }
  return 0;
}
