#include "../importers.h"

// Função para montar distancias
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

// Função para enviar vetor distancia
void sendSignal() {
  char message[MESSAGE_SIZE];
  int index;

  // Manipula distancias colocando-as em uma string para envio
  pthread_mutex_lock(&distanceMt);
  handleDistances(message);
  pthread_mutex_unlock(&distanceMt);

  // Envia distancias para todos os vizinhos
  for (index = 0; index < information->numberOfConnections; index++) {
    Structure *structure = generateStructure(
      getRouter(information->connectedRouters[index].id),
      message,
      CONTROL_TYPE
    );

    // Coloca estrutura com distancia na fila de saida
    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, structure);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

// Função para verificar se conexão está ativa
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

// Função para gerenciar envio do vetor distancia
void *signalFn() {
  while (true) {
    checkConnection();
    sendSignal();
    sleep(SIGNAL_TIME);
  }
}