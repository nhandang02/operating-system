#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

#include<semaphore.h>

#define MAX_FARMER 10
pthread_t tid[MAX_FARMER];
sem_t mutex_sem;

void * farmer(void * param, int n) {
  int v = * (int * ) param;  free(param);
  printf("\n%d Arriving bridge ...", v);
  sem_wait( & mutex_sem);
  printf("\n%d Enter bridge ...", v);

  int value;
  sem_getvalue(&mutex_sem, &value);
  printf("\nNumber of people on the bridge: %d", n - value + 1);

  sleep(rand() % 5 + 3); //random time cost 2 --> 6 s
  printf("\n%d Leaving bridge ...", v);
  sem_post( & mutex_sem);
  return NULL;
}

int main(int argc, char * argv[]) {
  int n = atoi(argv[1]);
  //intializes control init
  sem_init( & mutex_sem, 0, n);
  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time( & t));
  for (int i = 0; i < MAX_FARMER; i++) {
    int * p = malloc(sizeof i);* p = i;
    pthread_create( & tid[i], NULL, farmer, p);
    sleep(rand() % 3); //random time cost 0-4 s
  }
  for (int i = 0; i < MAX_FARMER; i++)
    pthread_join(tid[i], NULL);
  return 0;
}
