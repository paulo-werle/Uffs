#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER, mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_t Thread1, Thread2;

void *thread1(void *data){
  int mutex1Locked = 1, mutex2Locked = 1;
  int i;
  
  while ( mutex1Locked ){
    mutex1Locked = pthread_mutex_trylock(&mutex1);
    sleep(1);
  }
  if ( !mutex1Locked ){
    printf("Thread1 ID %ld got mutex1.\n", pthread_self());
    for ( i = 0; i < 10000000; ++i );

  } else {
    printf("Thread1 ID: %ld did not get mutex1.\n", pthread_self());
  }
  pthread_mutex_unlock(&mutex1);

  while ( mutex2Locked ){
    mutex2Locked = pthread_mutex_trylock(&mutex2);
    sleep(1);
  }
  if ( !mutex2Locked ){
    printf("Thread1 ID %ld got mutex2.\n", pthread_self());
    for ( i = 0; i < 10000000; ++i );

  } else {
    printf("Thread1 ID: %ld did not get mutex2.\n", pthread_self());
  }
  pthread_mutex_unlock(&mutex2);
  pthread_exit(NULL);
}

void *thread2(void *data){
  int mutex1Locked = 1, mutex2Locked = 1;
  int i;
  
  while ( mutex2Locked ){
    mutex2Locked = pthread_mutex_trylock(&mutex2);
    sleep(1);
  }
  if ( !mutex2Locked ){
    printf("Thread2 ID %ld got mutex2.\n", pthread_self());
    for ( i = 0; i < 10000000; ++i );

  } else {
    printf("Thread2 ID: %ld did not get mutex2.\n", pthread_self());
  }
  pthread_mutex_unlock(&mutex2);

  while ( mutex1Locked ){
    mutex1Locked = pthread_mutex_trylock(&mutex1);
    sleep(1);
  }
  if ( !mutex1Locked ){
    printf("Thread2 ID %ld got mutex1.\n", pthread_self());
    for ( i = 0; i < 10000000; ++i );

  } else {
    printf("Thread2 ID: %ld did not get mutex1.\n", pthread_self());
  }
  pthread_mutex_unlock(&mutex1);
  pthread_exit(NULL);
}

int main(){
  pthread_create(&Thread1, NULL, thread1, NULL);
  pthread_create(&Thread2, NULL, thread2, NULL);

  pthread_join(Thread1, NULL);
  pthread_join(Thread2, NULL);
  printf("Thread ID: %ld returned\n", Thread1);
  printf("Thread ID: %ld returned\n", Thread2);

  return 1;
}