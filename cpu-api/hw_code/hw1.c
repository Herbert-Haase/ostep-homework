#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    perror("fork failed");
  } else if(rc == 0){
    printf("child: x is %d\n",x);
    ++x;
    printf("child: x updated to %d\n",x);
  } else {
    printf("parent: x is %d\n",x);
    ++x;
    printf("parent: x updated to %d\n",x);
  }
  return 0;
}
