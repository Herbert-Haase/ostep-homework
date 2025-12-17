#include "common_threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t
{
  sem_t mutex;
  sem_t turnstile;
} ns_mutex_t;

ns_mutex_t m;
int count;
pthread_t t1, t2;

void ns_mutex_init(ns_mutex_t *m) {
  sem_init(&m->mutex, 0,1);
  sem_init(&m->turnstile, 0,1);
}

void ns_mutex_acquire(ns_mutex_t *m) {
  sem_wait(&m->turnstile);
  sem_wait(&m->mutex);
  sem_post(&m->turnstile);
}

void ns_mutex_release(ns_mutex_t *m) {
  sem_post(&m->mutex);
}

void *worker(void *arg) { 
  ns_mutex_acquire(&m);
  count++;
  ns_mutex_release(&m);
  return NULL; }

int main(int argc, char *argv[])
{
  ns_mutex_init(&m);
  pthread_create(&t1,NULL,worker,NULL);
  pthread_create(&t2,NULL,worker,NULL);
  printf("parent: begin\n");
  printf("parent: end\n");
  return 0;
}
