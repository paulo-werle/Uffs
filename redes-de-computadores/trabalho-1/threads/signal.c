#include "../dataStructure.c"
#include "../importers.h"

void sendSignal() {
  int idx;

  for (idx = 0; idx < information->connectionsNumber; idx++) {
    MessageStructure *msg = createStructure(
      &(information->connections[idx]),
      information->distances,
      CONTROL_TYPE
    );

    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, msg);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

void *signalFn() {
  sendSignal();
}