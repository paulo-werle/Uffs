#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>

#include "data_structures.c"
#include "functions.h"

int routerId;
CurrentRouterInformation *currentRouterInformation;

sem_t semaphoreForTerminal;
sem_t semaphoreForSending;

// Inicia Semaphores
void initSemaphores() {
  sem_init(&semaphoreForSending, 0, 0);
  sem_init(&semaphoreForTerminal, 0, 0);
}

// Destroi Semaphores
void destroySemaphores() {
  sem_destroy(&semaphoreForSending);
}

// Manipula Threads
void manipulateThreads() {
  pthread_t threadSender;
  pthread_t threadTerminal;

  pthread_create(&threadSender, NULL, &senderFunction, NULL);
  pthread_create(&threadTerminal, NULL, &terminalFunction, NULL);

  pthread_join(threadSender, NULL);
  pthread_join(threadTerminal, NULL);
}


int main(int numberOfArguments, char *arguments[]) {

  // Faz a validação nos argumentos
  validateArgument(numberOfArguments, arguments);
  routerId = atoi(arguments[1]);

  // Procura roteadores conectados
  currentRouterInformation = configureRouter(routerId);

  // Inicia Semaphores
  initSemaphores();

  // Manipula Threads
  manipulateThreads();

  // Destroi Semaphores
  destroySemaphores();

  return 0;
}

// pthread_t threadReceiver, threadSender, threadPacketHandler, threadTerminal;

// Inicia threads para serviços
// pthread_create(&threadReceiver,      NULL, &receiverFunction,      NULL);
// pthread_create(&threadSender,        NULL, &senderFunction,        NULL);
// pthread_create(&threadPacketHandler, NULL, &packetHandlerFunction, NULL);
// pthread_create(&threadTerminal,      NULL, &terminalFunction,      NULL);

// pthread_join(threadReceiver,      NULL);
// pthread_join(threadSender,        NULL);
// pthread_join(threadPacketHandler, NULL);
// pthread_join(threadTerminal,      NULL);


//  = startList();
// for (int i = 0; i <= 15; i++) {
//   Structure *structure = malloc( sizeof(Structure) );
//   structure->messageType = i;
//   entryQueue = insertInTheList(entryQueue, structure);
// }

// while (entryQueue->next != NULL) {
//   printf("%d \n", entryQueue->structure->messageType);
//   entryQueue = removeFromList(entryQueue);
// }
// printf("%d \n", entryQueue->structure->messageType);