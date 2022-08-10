#include "dataStructure.c"
#include "importers.h"

// Informações do roteador
Information *information;

// Listas
List *entryList;
List *exitList;
List *receiverList;

// Threads
pthread_t terminalTh;
pthread_t senderTh;
pthread_t receiverTh;
pthread_t packetHandlerTh;

// Mutexes
pthread_mutex_t entryMt;
pthread_mutex_t exitMt;
pthread_mutex_t receiverMt;

// Semáforos
sem_t senderSm;
sem_t packetHandlerSm;

// Socket
int sSocket;
struct sockaddr_in senderAddr;
struct sockaddr_in receiverAddr;

void createSemaphores() {
  sem_init(&senderSm,        0, 0);
  sem_init(&packetHandlerSm, 0, 0);
}

void destroySemaphores() {
  sem_destroy(&senderSm);
  sem_destroy(&packetHandlerSm);
}

void createThreads() {
  pthread_create(&terminalTh,      NULL, &terminalFn,      NULL);
  pthread_create(&senderTh,        NULL, &senderFn,        NULL);
  pthread_create(&receiverTh,      NULL, &receiverFn,      NULL);
  pthread_create(&packetHandlerTh, NULL, &packetHandlerFn, NULL);
}

void destroyThreads() {
  pthread_join(terminalTh,      NULL);
  pthread_join(senderTh,        NULL);
  pthread_join(receiverTh,      NULL);
  pthread_join(packetHandlerTh, NULL);
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