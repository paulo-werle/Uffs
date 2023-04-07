#include "../importers.h"

// Função para receber pacotes
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

// Função para gerenciar recebimento
void *receiverFn() {
  Structure *structure;

  while(true) {
    // Recebe pacote
    structure = receiverMessage();

    // Coloca na fila de manipulação de pacotes
    pthread_mutex_lock(&entryMt);
    entryList = insertInTheList(entryList, structure);
    pthread_mutex_unlock(&entryMt);
    sem_post(&packetHandlerSm);
  }
}