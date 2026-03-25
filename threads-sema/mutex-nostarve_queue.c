#include "common_threads.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 32

typedef struct __queue
{
  sem_t *data[N];
  int size;
  int max_size;
  int front;
  int back;
} queue;

void init_queue(queue *q)
{
  q->size = 0;
  q->max_size = N;
  q->front = 0;
  q->back = N - 1;
}

void queue_overflow(void)
{
  fprintf(stderr, "queue overflow: %s at %d\n", __FILE__, __LINE__);
  exit(1);
}

void queue_underflow(void)
{
  fprintf(stderr, "queue underflow: %s at %d\n", __FILE__, __LINE__);
  exit(1);
}

bool isfull(const queue *self) { return self->size == self->max_size; }

bool isempty(const queue *self) { return self->size == 0; }

void push(queue *self, sem_t *value)
{
  if (isfull(self))
    queue_overflow();
  self->back = (self->back + 1) % self->max_size;
  self->data[self->back] = value;
  self->size++;
}

sem_t *pop(queue *self)
{
  if (isempty(self))
    queue_underflow();
  sem_t *x = self->data[self->front];
  self->front = (self->front + 1) % self->max_size;
  self->size--;
  return x;
}

//
// No-starve mutex implementation using FIFO queue
//

typedef struct __ns_mutex_t
{
  queue q;     // FIFO queue of waiting threads
  sem_t guard; // Protects queue operations
  sem_t mutex; // The actual mutex lock
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m)
{
  init_queue(&m->q);
  sem_init(&m->guard, 0, 1); // Guard initialized to 1 (unlocked)
  sem_init(&m->mutex, 0, 1); // Mutex initialized to 1 (unlocked)
}

void ns_mutex_acquire(ns_mutex_t *m, sem_t *sem)
{
  // Initialize the thread's personal semaphore to 0 (blocked)
  sem_init(sem, 0, 0);

  // Enter critical section to access queue
  sem_wait(&m->guard);

  if (isempty(&m->q))
  {
    // Queue is empty - try to acquire mutex directly
    sem_post(&m->guard); // Release guard first
    sem_wait(&m->mutex); // Acquire the mutex
  }
  else
  {
    // Queue has waiting threads - join the queue
    push(&m->q, sem);
    sem_post(&m->guard); // Release guard
    sem_wait(sem);       // Wait on personal semaphore
    // When woken up, we have the mutex
  }
}

void ns_mutex_release(ns_mutex_t *m)
{
  // Enter critical section to access queue
  sem_wait(&m->guard);

  if (isempty(&m->q))
  {
    // No one waiting - just release the mutex
    sem_post(&m->mutex);
  }
  else
  {
    // Wake up the next thread in queue (FIFO order)
    sem_t *next = pop(&m->q);
    sem_post(next); // Signal the next thread
  }

  sem_post(&m->guard);
}

//
// Test code
//

ns_mutex_t lock;
int counter = 0;
int iterations = 10;

void *worker(void *arg)
{
  int thread_id = *(int *)arg;
  sem_t my_sem; // Each thread has its own semaphore

  for (int i = 0; i < iterations; i++)
  {
    ns_mutex_acquire(&lock, &my_sem);

    // Critical section
    counter++;
    printf("Thread %d: counter = %d\n", thread_id, counter);
    usleep(100); // Simulate some work

    ns_mutex_release(&lock);

    usleep(50); // Simulate work outside critical section
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  printf("parent: begin\n");

  int num_threads = 5;
  if (argc > 1)
  {
    num_threads = atoi(argv[1]);
  }
  if (argc > 2)
  {
    iterations = atoi(argv[2]);
  }

  pthread_t threads[num_threads];
  int thread_ids[num_threads];

  ns_mutex_init(&lock);

  // Create worker threads
  for (int i = 0; i < num_threads; i++)
  {
    thread_ids[i] = i;
    Pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
  }

  // Wait for all threads to complete
  for (int i = 0; i < num_threads; i++)
  {
    Pthread_join(threads[i], NULL);
  }

  printf("parent: end (final counter = %d, expected = %d)\n", counter,
         num_threads * iterations);

  return 0;
}
