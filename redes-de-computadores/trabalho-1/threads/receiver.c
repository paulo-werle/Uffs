#include "../dataStructure.c"
#include "../importers.h"

Structure *receiverMessage() {
  Structure *structure = malloc(sizeof(Structure));
  unsigned int lenSocket = sizeof(receiverAddr);
  int code;

  code = recvfrom(
    sSocket, structure, sizeof(Structure), 0,
    (struct sockaddr *) &receiverAddr, &lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem \n");

  return structure;
}

void *receiverFn() {
  Structure *structure;

  while(true) {
    structure = receiverMessage();

    // printStructure(structure);
    pthread_mutex_lock(&entryMt);
    entryList = insertInTheList(entryList, structure);
    pthread_mutex_unlock(&entryMt);
    sem_post(&packetHandlerSm);
  }
}