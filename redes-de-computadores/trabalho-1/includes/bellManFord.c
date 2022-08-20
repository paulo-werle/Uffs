#include "../dataStructure.c"
#include "../importers.h"

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

int getWeight(int id) {
  int index, value;

  for (index = 0; index < information->numberOfConnections; index++)
    if (id == information->connectedRouters[index].id) {
      value = information->connectedRouters[index].value;
      break;
    }

  return value;
}

int handleBellManFord(Distance *distances, int weight) {
  Distance *info, *dist;
  int indexX, indexY, changes = 0;

  for (indexX = 0; indexX <= information->numberOfRouters; indexX++) {
    for (indexY = 0; indexY <= information->numberOfRouters; indexY++) {
      info = &information->distances[indexX];
      dist = &distances[indexY];

      if (info->id == dist->id && info->value > dist->value + weight) {
        info->value = dist->value + weight;
        info->src = dist->src;
        changes++;
      }
    }
  }

  return changes;
}

int bellManFord(char message[]) {
  Distance *distances;
  int weight, changes;

  distances = handleMessage(message);
  weight = getWeight(distances[0].id);

  pthread_mutex_lock(&distanceMt);
  changes = handleBellManFord(distances, weight);
  pthread_mutex_unlock(&distanceMt);

  return changes;
}