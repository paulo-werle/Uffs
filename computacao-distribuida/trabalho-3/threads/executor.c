#include "../importers.h"

// Função: countAcks
//   description: Conta quantidade de acks correspondente
//   params: null
//   return: null
int countAcks(Structure *structure) {
  List *auxList = ackList;
  int number = 0;

  while (auxList->next != NULL) {
    if (
      auxList->structure->relativeTime == structure->relativeTime &&
      !strcmp(auxList->structure->message, structure->message)
    ) {
      number++;
    }

    auxList = auxList->next;
  }

  return number;
}

void removeAcks(Structure *structure) {
  List *removeList, *auxList = ackList;

  while (auxList->next != NULL) {
    removeList = NULL;

    if (
      auxList->structure->relativeTime == structure->relativeTime &&
      auxList->structure->index == structure->index &&
      !strcmp(auxList->structure->message, structure->message)
    ) {
      removeList = auxList;
    }

    auxList = auxList->next;
    if (removeList != NULL) {
      removeList = removeFromList(removeList);
    }
  }
}

// Função: execute
//   description: Responsavel por executar as operações das mensagens confirmadas
//   params: null
//   return: null
void execute(Structure *structure) {

  // Verifica se tem conexões suficiente para executar
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

    pthread_mutex_lock(&ackMt);
    execute(ackList->structure);
    pthread_mutex_unlock(&ackMt);
  }
}