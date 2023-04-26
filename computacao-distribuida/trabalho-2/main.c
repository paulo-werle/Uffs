#include "importers.h"

// Informações do roteador
Router *router;

// Listas
List *entryList;
List *exitList;
List *dataList;

// Threads
pthread_t terminalTh;
pthread_t senderTh;
pthread_t receiverTh;
pthread_t packetHandlerTh;

// Mutexes
pthread_mutex_t entryMt;
pthread_mutex_t exitMt;
pthread_mutex_t dataMt;

// Semáforos
sem_t senderSm;
sem_t packetHandlerSm;

// Socket
int sSocket;
struct sockaddr_in senderAddr;
struct sockaddr_in receiverAddr;

// Função: createSemaphores
//   description: Responsavel por iniciar os semáforos
//   params: null
//   return: null
void createSemaphores() {
  sem_init(&senderSm,        0, 0);
  sem_init(&packetHandlerSm, 0, 0);
}

// Função: destroySemaphores
//   description: Responsavel por destruir os semáforos
//   params: null
//   return: null
void destroySemaphores() {
  sem_destroy(&senderSm);
  sem_destroy(&packetHandlerSm);
}

// Função: createThreads
//   description: Responsavel por criar as threads
//   params: null
//   return: null
void createThreads() {
  pthread_create(&terminalTh,      NULL, &terminalFn,      NULL);
  pthread_create(&receiverTh,      NULL, &receiverFn,      NULL);
  pthread_create(&packetHandlerTh, NULL, &packetHandlerFn, NULL);
  pthread_create(&senderTh,        NULL, &senderFn,        NULL);
}

// Função: destroyThreads
//   description: Responsavel por destruir as threads
//   params: null
//   return: null
void destroyThreads() {
  pthread_join(terminalTh,      NULL);
  pthread_join(receiverTh,      NULL);
  pthread_join(packetHandlerTh, NULL);
  pthread_join(senderTh,        NULL);
}

int main(int number, char *args[]) {
  // Argumentos de inicialização
  router = handleArguments(number, args);

  // Inicia sockets
  startSocket();

  // Manipula threads e semáforos
  createSemaphores();
  createThreads();
  destroyThreads();
  destroySemaphores();

  return 0;
}