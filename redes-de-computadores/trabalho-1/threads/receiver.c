#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "../dataStructure.c"
#include "../importers.h"

#define ERROR_CODE -1

// Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

void receiverMessage() {
  int lenSocket = sizeof(receiverAddr);
  MessageStructure *msg = malloc( sizeof(MessageStructure) );
  int code;

  code = recvfrom(
    sSocket, msg, sizeof(MessageStructure), 0,
    (struct sockaddr *) &receiverAddr, &lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem \n");
}

void *receiverFn() {
  while(true) {
    receiverMessage();
  }
}