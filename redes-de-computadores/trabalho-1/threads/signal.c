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

  pthread_mutex_lock(&distanceMt);
  handleDistances(message);
  pthread_mutex_unlock(&distanceMt);

  for (index = 0; index < information->numberOfConnections; index++) {
    Structure *structure = generateStructure(
      getRouter(information->connectedRouters[index].id),
      message,
      CONTROL_TYPE
    );

    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, structure);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

void checkConnection() {
  time_t checkTime = time(NULL);
  int index;

  for (index = 0; index <= information->numberOfRouters; index++) {
    if (
      information->distances[index].time &&
      (checkTime - information->distances[index].time) >= DISCONECT_TIME
    ) {
      information->distances[index].time = 0;
      information->distances[index].value = INFINITE;
    }
  }
}

void *signalFn() {
  while (true) {
    checkConnection();
    sendSignal();
    sleep(SIGNAL_TIME);
  }
}