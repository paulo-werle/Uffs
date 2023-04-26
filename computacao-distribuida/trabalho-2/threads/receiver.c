#include "../importers.h"

// Função: receiverFn
//   description: Responsavel por receber a estrutura
//   params: null
//   return: structure<Structure>
Structure *receiverMessage() {
  Structure *structure = malloc(sizeof(Structure));
  unsigned int lenSocket = sizeof(receiverAddr);
  int code;

  // Recebe pacote
  code = recvfrom(
    sSocket, structure, sizeof(Structure), 0,
    (struct sockaddr *) &receiverAddr, &lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem \n");

  return structure;
}

// Função: receiverFn
//   description: Responsavel por gerenciar o recebimento
//   params: null
//   return: null
void *receiverFn() {
  Structure *structure;

  while(true) {
    structure = receiverMessage();

    pthread_mutex_lock(&entryMt);
    entryList = insertInTheList(entryList, structure);
    pthread_mutex_unlock(&entryMt);
    sem_post(&packetHandlerSm);
  }
}