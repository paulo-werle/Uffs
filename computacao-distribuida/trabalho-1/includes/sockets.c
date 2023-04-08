#include "../importers.h"

// Função: prepareSocketToSend
//   description: Responsavel por iniciar o socket de envio
//   params: null
//   return: null
void prepareSocketToSend() {
  memset((char *) &senderAddr, 0, sizeof(senderAddr));
  senderAddr.sin_family = AF_INET;
}

// Função: prepareSocketToReceiver
//   description: Responsavel por iniciar o socket de recebimento
//   params: null
//   return: null
void prepareSocketToReceiver() {
  int bindCode;

  memset((char *) &receiverAddr, 0, sizeof(receiverAddr));
  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(router->port);
  receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bindCode = bind(sSocket, (struct sockaddr *)&receiverAddr, sizeof(receiverAddr));

  if (bindCode == ERROR_CODE)
    reportError("PrepareSocketToReceiver - bind error\n");
}

// Função: startSocket
//   description: Responsavel por iniciar os sockets
//   params: null
//   return: null
void startSocket() {
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sSocket == ERROR_CODE)
    reportError("Socket - sSocket error\n");

  prepareSocketToSend();
  prepareSocketToReceiver();
}