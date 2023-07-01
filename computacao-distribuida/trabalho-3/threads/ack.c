#include "../importers.h"

bool compareRelativeTimeAndIndex(int time, int index) {
  return (relativeTime >= time);
}

void scheduleConfirmationSending(Structure *structure) {
  for (int index = 0; index < connections->number; index++) {
    Structure *auxStructure = generateAckStructure(&connections->routers[index], structure);

    // Coloca estrutura na fila de saida
    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, auxStructure);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

void senderAck() {
  List *auxList = NULL, *list = msgList;

  while (list != NULL) {
    Structure *listStructure = list->structure;

    if ( compareRelativeTimeAndIndex(listStructure->relativeTime, listStructure->index)) {
      scheduleConfirmationSending(listStructure);

    } else {
      auxList = insertOrderedInTheList(auxList, listStructure);
    }

    list = list->next;
  }

  msgList = auxList;
}

// Função: ackFn
//   description: Responsavel por executar as operações das mensagens confirmadas
//   params: null
//   return: null
void *ackFn() {
  while(true) {
    sem_wait(&senderAckSm);

    senderAck();
  }
}