#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if (rc == 0) {
    puts("Hello!");
  } else {
    // for (int i = 0; i < 100000; ++i) {
    // }
    sleep(1);
    puts("Goodbye");
  }
  return 0;
}
