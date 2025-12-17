#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *cpu_intensive_work(void *arg)
{
  int id = *(int *)arg;

  // Infinite loop to max out one CPU core
  while (1)
  {
    // Busy work
    for (volatile int i = 0; i < 1000000; i++)
      ;
  }
  return NULL;
}

int main()
{
  pthread_t threads[4];
  int ids[4] = {0, 1, 2, 3};

  // Create 4 threads
  for (int i = 0; i < 4; i++)
  {
    pthread_create(&threads[i], NULL, cpu_intensive_work, &ids[i]);
  }

  sleep(10); // Let them run
  return 0;
}
// ```
//
// **What happens on a 4-core CPU:**
// ```
// Core 0: [Thread 1] ████████████████████ 100% busy
// Core 1: [Thread 2] ████████████████████ 100% busy
// Core 2: [Thread 3] ████████████████████ 100% busy
// Core 3: [Thread 4] ████████████████████ 100% busy
//
// Total CPU usage: 400% (4 cores × 100%)
