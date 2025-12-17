#include <stdio.h>
#include <pthread.h>

#include "common_threads.h"
pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

int balance = 0;

void* worker(void* arg) {
    pthread_mutex_lock(&global_lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&global_lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    pthread_mutex_lock(&global_lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&global_lock);
    Pthread_join(p, NULL);
    return 0;
}
