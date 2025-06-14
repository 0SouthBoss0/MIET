#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mut_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut_2 = PTHREAD_MUTEX_INITIALIZER;

void task1(void* _) {
  while (true) {
    printf("task1: mut_1 is to be locked\n");
    pthread_mutex_lock(&mut_1);
    printf("task1: mut_1 locked\n");
    sleep(2);
    pthread_mutex_lock(&mut_2);
    printf("task1: mut_2 locked\n");
    pthread_mutex_unlock(&mut_1);
    printf("task1: mut_1 unlocked\n");
    pthread_mutex_unlock(&mut_2);
    printf("task1: mut_2 unlocked\n");
  }
}

void task2(void* _) {
  while (true) {
    printf("task2: mut_2 is to be locked\n");
    pthread_mutex_lock(&mut_2);
    printf("task2: mut_2 locked\n");
    sleep(2);
    pthread_mutex_lock(&mut_1);
    printf("task2: mut_1 locked\n");
    pthread_mutex_unlock(&mut_2);
    printf("task2: mut_2 unlocked\n");
    pthread_mutex_unlock(&mut_1);
    printf("task2: mut_1 unlocked\n");
  }
}

int main() {
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, (void *)task1, NULL);
  pthread_create(&thread2, NULL, (void *)task2, NULL);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}