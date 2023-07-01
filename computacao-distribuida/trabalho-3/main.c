#include "importers.h"

// Informações do roteador
Router *router;
Connections *connections;
int relativeTime;

// Listas
List *entryList;  // Lista de entrada
List *exitList;   // Lista de saida
List *dataList;   // Lista de operações executadas
List *msgList;    // Lista de mensagens
List *ackList;    // Lista de confirmações

// Threads
pthread_t terminalTh;
pthread_t senderTh;
pthread_t receiverTh;
pthread_t packetHandlerTh;
pthread_t executorTh;
pthread_t ackTh;

// Mutexes
pthread_mutex_t entryMt;
pthread_mutex_t exitMt;
pthread_mutex_t dataMt;
pthread_mutex_t msgMt;
pthread_mutex_t ackMt;

// Semáforos
sem_t senderAckSm;
sem_t senderSm;
sem_t packetHandlerSm;
sem_t ackSm;

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
  sem_init(&ackSm,           0, 0);
  sem_init(&senderAckSm,     0, 0);
}

// Função: destroySemaphores
//   description: Responsavel por destruir os semáforos
//   params: null
//   return: null
void destroySemaphores() {
  sem_destroy(&senderSm);
  sem_destroy(&packetHandlerSm);
  sem_destroy(&ackSm);
  sem_destroy(&senderAckSm);
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
  pthread_create(&executorTh,      NULL, &executorFn,      NULL);
  pthread_create(&ackTh,           NULL, &ackFn,           NULL);
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
  pthread_join(executorTh,      NULL);
  pthread_join(ackTh,           NULL);
}

int main(int number, char *args[]) {
  srand(time(NULL));

  // Inicia tempo relativo
  relativeTime = 1;

  // Argumentos de inicialização
  router = handleArguments(number, args);
  setConnections();

  // Inicia sockets
  startSocket();

  // Manipula threads e semáforos
  createSemaphores();
  createThreads();
  destroyThreads();
  destroySemaphores();

  return 0;
}