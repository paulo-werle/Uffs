#include "../importers.h"

// Função para pegar distancias na string
Distance *handleMessage(char message[]) {
  Distance *distances = malloc(sizeof(Distance) * (information->numberOfRouters + 1));
  char values[MESSAGE_SIZE];
  int index, size = 0;

  for (index = 0; index <= information->numberOfRouters; index++) {
    sscanf(
      &message[size], "|%d, %d, %d|",
      &distances[index].id, &distances[index].src, &distances[index].value
    );

    size += snprintf(
      &values[size], MESSAGE_SIZE, "|%d, %d, %d|",
      distances[index].id, distances[index].src, distances[index].value
    );
  }

  return distances;
}

// Função para pegar peso que devemos considerar nas conexões
int getWeight(int id) {
  int index, value;

  for (index = 0; index < information->numberOfConnections; index++)
    if (id == information->connectedRouters[index].id) {
      value = information->connectedRouters[index].value;
      break;
    }

  return value;
}

// Função para manipular BellMan Ford
int handleBellManFord(Distance *distances, int weight) {
  Distance *info, *dist;
  int indexX, indexY, changes = 0;

  // Verefica cada distancia do roteador com a distancia recebida
  for (indexX = 0; indexX <= information->numberOfRouters; indexX++) {
    for (indexY = 0; indexY <= information->numberOfRouters; indexY++) {
      info = &information->distances[indexX];
      dist = &distances[indexY];

      // Verefica se a distancia é do mesmo roteador e se é menor
      if (info->id == dist->id && info->value > dist->value + weight) {
        info->value = dist->value + weight;
        info->src = dist->src;
        changes++;
      }
    }
  }

  return changes;
}

// Função para gerenciar BellMan Ford
int bellManFord(char message[]) {
  Distance *distances;
  int weight, changes;

  // Pega distancias e peso
  distances = handleMessage(message);
  weight = getWeight(distances[0].id);

  // Faz a manipulação das distancias
  pthread_mutex_lock(&distanceMt);
  changes = handleBellManFord(distances, weight);
  pthread_mutex_unlock(&distanceMt);

  return changes;
}