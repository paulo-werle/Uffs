#include "../dataStructure.c"
#include "../importers.h"

void handleDataType(Structure *structure) {
  pthread_mutex_lock(&receiverMt);
  receiverList = insertInTheList(receiverList, structure);
  pthread_mutex_unlock(&receiverMt);
}

void handleControlType(Structure *structure) {
  pthread_mutex_lock(&controlMt);
  controlList = insertInTheList(controlList, structure);
  pthread_mutex_unlock(&controlMt);
}

void manageBellManFord(Structure *structure) {
  int changes = bellManFord(structure->message);
  if (changes) sendSignal();
}

void sortPackageType(Structure *structure){
  if (structure->type == CONTROL_TYPE) {
    handleControlType(structure);
    manageBellManFord(structure);
  }

  if (structure->type == DATA_TYPE) {
    handleDataType(structure);
    // TODO: Vamos ter que encaminhar para vizinhos
  }
}

void updateTime(Structure *structure) {
  int index;

  for (index = 0; index <= information->numberOfRouters; index++)
    if (structure->source.id == information->distances[index].id) {
      time(&information->distances[index].time);
      break;
    }
}

void *packetHandlerFn() {
  while(true) {
    sem_wait(&packetHandlerSm);
    updateTime(entryList->structure);
    sortPackageType(entryList->structure);

    pthread_mutex_lock(&entryMt);
    entryList = removeFromList(entryList);
    pthread_mutex_unlock(&entryMt);
  }
}