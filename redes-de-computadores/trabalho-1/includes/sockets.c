#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "../dataStructure.c"
#include "../importers.h"

#define ERROR_CODE -1

// Informações do roteador
extern Information *information;

// Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

void prepareSocketToSend() {
  memset((char *) &senderAddr, 0, sizeof(senderAddr));
  senderAddr.sin_family = AF_INET;
  // senderAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void prepareSocketToReceiver() {
  int bindCode;

  memset((char *) &receiverAddr, 0, sizeof(receiverAddr));
  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(information->current->port);
  receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bindCode = bind(sSocket, (struct sockaddr *)&receiverAddr, sizeof(receiverAddr));

  if (bindCode == ERROR_CODE)
    reportError("PrepareSocketToReceiver - bind error\n");
}

void startSocket() {
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sSocket == ERROR_CODE)
    reportError("Socket - sSocket error\n");

  prepareSocketToSend();
  prepareSocketToReceiver();
}