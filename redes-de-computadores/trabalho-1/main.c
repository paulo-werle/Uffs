#include "importers.h"

// Informações do roteador
Information *information;

// Listas
List *entryList;
List *exitList;
List *receiverList;
List *controlList;

// Threads
pthread_t terminalTh;
pthread_t senderTh;
pthread_t receiverTh;
pthread_t packetHandlerTh;
pthread_t signalTh;

// Mutexes
pthread_mutex_t entryMt;
pthread_mutex_t exitMt;
pthread_mutex_t receiverMt;
pthread_mutex_t controlMt;
pthread_mutex_t distanceMt;

// Semáforos
sem_t senderSm;
sem_t packetHandlerSm;

// Socket
int sSocket;
struct sockaddr_in senderAddr;
struct sockaddr_in receiverAddr;

// Função para criar semáforos
void createSemaphores() {
  sem_init(&senderSm,        0, 0);
  sem_init(&packetHandlerSm, 0, 0);
}

// Função para destruir semáforos
void destroySemaphores() {
  sem_destroy(&senderSm);
  sem_destroy(&packetHandlerSm);
}

// Função para criar threads
void createThreads() {
  pthread_create(&terminalTh,      NULL, &terminalFn,      NULL);
  pthread_create(&receiverTh,      NULL, &receiverFn,      NULL);
  pthread_create(&packetHandlerTh, NULL, &packetHandlerFn, NULL);
  pthread_create(&senderTh,        NULL, &senderFn,        NULL);
  pthread_create(&signalTh,        NULL, &signalFn,        NULL);
}

// Função para destruir threads
void destroyThreads() {
  pthread_join(terminalTh,      NULL);
  pthread_join(receiverTh,      NULL);
  pthread_join(packetHandlerTh, NULL);
  pthread_join(senderTh,        NULL);
  pthread_join(signalTh,        NULL);
}

int main(int number, char *args[]) {
  // Verefica argumento de inicialização
  int id = executionArguments(number, args);

  // Define informações sobre o roteador
  setInformation(id);

  // Inicia socket
  startSocket();

  // Manipula threads e semáforos
  createSemaphores();
  createThreads();
  destroyThreads();
  destroySemaphores();

  return 0;
}