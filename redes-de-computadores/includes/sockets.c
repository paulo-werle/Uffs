#include "../importers.h"

// Função para preparar socket de envio
void prepareSocketToSend() {
  memset((char *) &senderAddr, 0, sizeof(senderAddr));
  senderAddr.sin_family = AF_INET;
}

// Função para preparar socket de recebimento
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

// Função para iniciar sockets
void startSocket() {
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sSocket == ERROR_CODE)
    reportError("Socket - sSocket error\n");

  prepareSocketToSend();
  prepareSocketToReceiver();
}