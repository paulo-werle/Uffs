#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutexCount      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  mutexCondition0  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  mutexCondition1  = PTHREAD_COND_INITIALIZER;
int globalCount = 0;

void *threadFunction();
void *threadFunction0(void* arg);
void *threadFunction1(void* arg);
void *threadFunction2(void* arg);

void main() {
  // Thread principal
  pthread_t thread;
  pthread_create( &thread, NULL, &threadFunction, NULL);
  pthread_join( thread, NULL);

  exit(EXIT_SUCCESS);
}

void *threadFunction() {
  int maxCount;
  printf("Informe até quanto se deve incrementar \n");
  scanf("%d", &maxCount);

  // Thread secundarias - inicia
  pthread_t thread0, thread1, thread2;

  // Thread secundarias - chama
  pthread_create( &thread0, NULL, &threadFunction0, (void *) &(maxCount) );
  pthread_create( &thread1, NULL, &threadFunction1, (void *) &(maxCount) );
  pthread_create( &thread2, NULL, &threadFunction2, (void *) &(maxCount) );

  // Thread secundarias - retorna
  pthread_join( thread0, NULL);
  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
}

void *threadFunction0(void* arg){
  int maxCount = *((int *) arg);

  for(;;) {
    if (globalCount >= maxCount) return(NULL);

    pthread_mutex_lock( &mutexCount );
    pthread_cond_wait( &mutexCondition0, &mutexCount );
    printf("Thread 0: globalCount: %d \n", ++globalCount );
    pthread_mutex_unlock( &mutexCount );

    // Colocado sleep para poder esperar variavel ser incrementada
    // pois caso não haver esse tempo, não cai no return
    sleep(0.5);
  }
}

void *threadFunction1(void* arg){
  int maxCount = *((int *) arg);

  for(;;) {
    if (globalCount >= maxCount) return(NULL);

    pthread_mutex_lock( &mutexCount );
    pthread_cond_wait( &mutexCondition1, &mutexCount );
    printf("Thread 1: globalCount: %d \n", ++globalCount );
    pthread_mutex_unlock( &mutexCount );

    // Colocado sleep para poder esperar variavel ser incrementada
    // pois caso não haver esse tempo, não cai no return
    sleep(0.5);
  }
}

void *threadFunction2(void* arg){
  int maxCount = *((int *) arg);

  for(;;) {

    pthread_mutex_lock( &mutexCount );
    switch (globalCount % 3) {
      case 0:
        pthread_mutex_unlock( &mutexCount );
        pthread_cond_signal( &mutexCondition0 );
      break;
      case 1:
        pthread_mutex_unlock( &mutexCount );
        pthread_cond_signal( &mutexCondition1 );
      break;
      case 2:
        printf("Thread 2: globalCount: %d \n", ++globalCount );
        pthread_mutex_unlock( &mutexCount );
      break;
    }
    if (globalCount >= maxCount) return(NULL);
  }
}