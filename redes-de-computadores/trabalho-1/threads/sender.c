#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "../dataStructure.c"
#include "../importers.h"

#define ERROR_CODE -1

// Listas
extern List *exitList;

// Semáforos
extern sem_t senderSm;

// Socket
extern int sSocket;
extern struct sockaddr_in socketAddr;

void sendMessageTo(MessageStructure *msg) {
  int lenSocket = sizeof(socketAddr);

  int code = sendto(
    sSocket, msg->message, strlen(msg->message), 0,
    (struct sockaddr *) &socketAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

void *senderFn() {

  while(true) {
    sem_wait(&senderSm);
    printf("Chegou uma mensagem aqui \n");

    sendMessageTo(exitList->messageStructure);
    exitList = removeFromList(exitList);
  }
  // List *aux = exitList;
  // while (aux != NULL) {
  //   printf("%s \n", aux->messageStructure->message);
  //   aux = aux->next;
  // }
  // printf("Veio para a thread de envio \n");
}