#include "../dataStructure.c"
#include "../importers.h"

void handleDataType(MessageStructure *msg) {
  pthread_mutex_lock(&receiverMt);
  receiverList = insertInTheList(receiverList, msg);
  pthread_mutex_unlock(&receiverMt);
}

void handleControlType(MessageStructure *msg) {
  pthread_mutex_lock(&controlMt);
  controlList = insertInTheList(controlList, msg);
  pthread_mutex_unlock(&controlMt);
}

void sortPackageType(MessageStructure *msg){
  if (msg->type == CONTROL_TYPE) {
    handleControlType(msg);
    // TODO: Vamos ter que aplicar o BellmanFord
  }

  else if (msg->type == DATA_TYPE) {
    handleDataType(msg);
    // TODO: Vamos ter que encaminhar para vizinhos
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