#include "../importers.h"

// Função: packetHandlerFn
//   description: Responsavel por gerenciar os pacotes recebidos
//   params: null
//   return: null
void *packetHandlerFn() {
  while(true) {
    sem_wait(&packetHandlerSm);

    // Insere na lista de dados
    pthread_mutex_lock(&dataMt);
    dataList = insertInTheList(dataList, entryList->structure);
    pthread_mutex_unlock(&dataMt);

    // Remove da lista de saida
    pthread_mutex_lock(&entryMt);
    entryList = removeFromList(entryList);
    pthread_mutex_unlock(&entryMt);
  }
}