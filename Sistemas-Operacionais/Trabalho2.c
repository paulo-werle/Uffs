#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// ----- Definições -----
#define N        5
#define LEFT     (i+N-1)%N
#define RIGHT    (i+1)%N
#define THINKING 0
#define HUNGRY   1
#define EATING   2

// ----- Tipos -----
int state[N];
sem_t mutex;
sem_t s[N];
pthread_t threads[N];

// ----- Declaração -----
void eat(int i);
void down(sem_t *mutex);
void put_forks(int i);
void take_forks(int i);
void test(int i);
void think(int i);
void up(sem_t *mutex);

// ----- Funções principais -----
void* philosopher(void* arg) {
  int i = *((int *) arg);

  while (true) {
    think(i);
    take_forks(i);
    eat(i);
    put_forks(i);
  }
}

void take_forks(int i) {
  down(&mutex);

  printf("O filósofo %d está FAMINTO \n", i);
  state[i] = HUNGRY;

  test(i);
  up(&mutex);
  down(&s[i]);
}

void put_forks(int i) {
  down(&mutex);
  
  printf("O filósofo %d está PENSANDO \n", i);
  state[i] = THINKING;

  test(LEFT);
  test(RIGHT);
  up(&mutex);
}

void test(int i) {
  printf("O filósofo %d gostaria de COMER \n", i);
  
  if ( state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING ) {
    printf("O filósofo %d pode COMER \n", i);
    state[i] = EATING;

    up(&s[i]);
  }
}

// ----- Funções Secundarias -----
void think(int i) {
  int time = rand() % 10 + 1;
  printf("O filósofo %d está PENSANDO por %d segundos \n", i, time);

  sleep( time );
}
void eat(int i) {
  int time = rand() % 10 + 1; 
  printf("O filósofo %d está COMENDO por %d segundos \n", i, time);

  sleep( time );
}

void up(sem_t *mutex) {
  sem_post(mutex);
}
void down(sem_t *mutex) {
  sem_wait(mutex);
}


int main(){
  // Variaveis auxiliares
  int count;

  // Semafaro - região critica
  sem_init(&mutex, 0, 1);

  // Semafaros - filósofos
  for (count = 0; count < N; count++) {
    sem_init(&s[count], 0, 1);
  }

  // Threads
  for (count = 0; count < N; count++) {
    pthread_create(&threads[count], NULL, philosopher, (void *) &(count));
  }

  // Threads
  for (count = 0; count < N; count++) {
    pthread_join(threads[count], NULL);
  }

  // Semafaros - filósofos
  for (count = 0; count < N; count++) {
    sem_destroy(&s[count]);
  }

  // Semafaro - região critica
  sem_destroy(&mutex);

  return 0;
}