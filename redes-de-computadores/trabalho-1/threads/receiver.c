#include "../dataStructure.c"
#include "../importers.h"

MessageStructure *receiverMessage() {
  int lenSocket = sizeof(receiverAddr);
  MessageStructure *msg = malloc( sizeof(MessageStructure) );
  int code;

  code = recvfrom(
    sSocket, msg, sizeof(MessageStructure), 0,
    (struct sockaddr *) &receiverAddr, &lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem \n");

  return msg;
}

void *receiverFn() {
  MessageStructure *msg;

  while(true) {
    // Recebe mensagem
    msg = receiverMessage();

    // Inserindo na lista de entrada
    pthread_mutex_lock(&entryMt);
    entryList = insertInTheList(entryList, msg);
    pthread_mutex_unlock(&entryMt);
  }
}