#include "../dataStructure.c"
#include "../importers.h"

void handleDistances(char message[]) {
  int index, size = 0;

  for (index = 0; index <= information->numberOfRouters; index++)
    size += snprintf(
      &message[size],
      MESSAGE_SIZE,
      "|%d, %d, %d|",
      information->distances[index].id,
      information->id,
      information->distances[index].value
    );
}

void sendSignal() {
  char message[MESSAGE_SIZE];
  int index;

  handleDistances(message);

  for (index = 0; index < information->numberOfConnections; index++) {
    Structure *structure = generateStructure(
      getRouter(information->connectedRouters[index].id),
      message,
      CONTROL_TYPE
    );

    // printStructure(structure);
    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, structure);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

void *signalFn() {
  while (true) {
    sendSignal();
    sleep(SIGNAL_TIME);
  }
}