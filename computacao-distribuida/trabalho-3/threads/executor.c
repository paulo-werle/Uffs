#include "../importers.h"

bool compareUuid(int uuid1, int uuid2) {
  return uuid1 == uuid2;
}

bool compareRelativeTimeAndIndexs(int time, int index) {
  return relativeTime >= time;
}

// Função: countAcks
//   description: Conta quantidade de acks correspondente
//   params: null
//   return: null
int countAcks(Structure *structure) {
  List *list = ackList;
  int number = 0;

  while (list != NULL) {
    Structure *listStructure = list->structure;

    if (
      compareUuid(listStructure->uuid, structure->uuid) &&
      compareRelativeTimeAndIndexs(structure->relativeTime, structure->index)
    ) {
      number++;
    }

    list = list->next;
  }

  return number;
}

void removeAcks(Structure *structure) {
  List *auxList = NULL, *list = ackList;

  while (list != NULL) {
    Structure *listStructure = list->structure;

    if (listStructure->uuid != structure->uuid) {
      auxList = insertOrderedInTheList(auxList, listStructure);
    }

    list = list->next;
  }

  ackList = auxList;
}

// Função: execute
//   description: Responsavel por executar as operações das mensagens confirmadas
//   params: null
//   return: null
void execute(Structure *structure) {

  if (countAcks(structure) == connections->number) {
    pthread_mutex_lock(&dataMt);
    dataList = insertInTheList(dataList, structure);
    pthread_mutex_unlock(&dataMt);

    removeAcks(structure);
  }
}

// Função: executorFn
//   description: Responsavel por executar as operações das mensagens confirmadas
//   params: null
//   return: null
void *executorFn() {
  while(true) {
    sem_wait(&ackSm);

    if (ackList != NULL) {
      pthread_mutex_lock(&ackMt);
      execute(ackList->structure);
      pthread_mutex_unlock(&ackMt);
    }
  }
}