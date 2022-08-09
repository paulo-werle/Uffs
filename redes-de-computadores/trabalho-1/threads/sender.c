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
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

void sendMessage(MessageStructure *msg) {
  int lenSocket = sizeof(senderAddr);
  int code;

  senderAddr.sin_port = htons(msg->destination.port);
  if (!inet_aton(msg->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");

  code = sendto(
    sSocket, msg, sizeof(MessageStructure), 0,
    (struct sockaddr *) &senderAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

void *senderFn() {
  while(true) {
    sem_wait(&senderSm);
    sendMessage(exitList->messageStructure);
    exitList = removeFromList(exitList);
  }
}