#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "dataStructure.c"
#include "importers.h"

// Informações do roteador
Information *information;

// Listas
List *entryList;
List *exitList;

// Threads
pthread_t terminalTh;
pthread_t senderTh;
pthread_t receiverTh;

// Mutexes
pthread_mutex_t exitMt;

// Semáforos
sem_t senderSm;

// Socket
int sSocket;
struct sockaddr_in senderAddr;
struct sockaddr_in receiverAddr;

void createSemaphores() {
  sem_init(&senderSm, 0, 0);
}

void destroySemaphores() {
  sem_destroy(&senderSm);
}

void createThreads() {
  pthread_create(&terminalTh, NULL, &terminalFn, NULL);
  pthread_create(&senderTh,   NULL, &senderFn,   NULL);
  pthread_create(&receiverTh, NULL, &receiverFn, NULL);
}

void destroyThreads() {
  pthread_join(terminalTh, NULL);
  pthread_join(senderTh,   NULL);
  pthread_join(receiverTh, NULL);
}

int main(int number, char *args[]) {

  // Define informações sobre o roteador
  int id = executionArguments(number, args);
  setInformation(id);

  // Inicia socket
  startSocket();

  // Manipula threads e semáforo
  createSemaphores();
  createThreads();
  destroyThreads();
  destroySemaphores();

  return 0;
}