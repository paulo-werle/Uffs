#include "../dataStructure.c"
#include "../importers.h"

void handleDataType(MessageStructure *msg) {
  pthread_mutex_lock(&receiverMt);
  receiverList = insertInTheList(receiverList, msg);
  pthread_mutex_unlock(&receiverMt);
}

void sortPackageType(MessageStructure *msg){
  if (msg->type == CONTROL_TYPE) {
    // TODO: Aqui devemos interpretar
  }

  if (msg->type == DATA_TYPE) {
    handleDataType(msg);
    // TODO: Falta encaminhar para vizinhos caso necessite
  }
}

void *packetHandlerFn() {
  while(true) {
    sem_wait(&packetHandlerSm);
    sortPackageType(entryList->messageStructure);

    pthread_mutex_lock(&entryMt);
    entryList = removeFromList(entryList);
    pthread_mutex_unlock(&entryMt);
  }
}