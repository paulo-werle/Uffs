#include "../importers.h"

// Função: typeAck
//   description: Responsavel por colocar estrutura na fila de mensagens
//   params: null
//   return: null
void typeMsg() {
  pthread_mutex_lock(&msgMt);
  msgList = insertOrderedInTheList(msgList, entryList->structure);
  pthread_mutex_unlock(&msgMt);
}

// Função: typeAck
//   description: Responsavel por colocar estrutura na fila de confirmações
//   params: null
//   return: null
void typeAck() {
  pthread_mutex_lock(&ackMt);
  ackList = insertOrderedInTheList(ackList, entryList->structure);
  pthread_mutex_unlock(&ackMt);
}

// Função: packetHandlerFn
//   description: Responsavel por gerenciar os pacotes recebidos
//   params: null
//   return: null
void *packetHandlerFn() {
  while(true) {
    sem_wait(&packetHandlerSm);

    // Insere na respectiva lista
    if (strcmp(entryList->structure->type, "msg") == 0) {
      typeMsg();
    }

    if (strcmp(entryList->structure->type, "ack") == 0) {
      typeAck();
    }

    // Remove da lista de saida
    pthread_mutex_lock(&entryMt);
    entryList = removeFromList(entryList);
    pthread_mutex_unlock(&entryMt);
  }
}