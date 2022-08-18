#include "../dataStructure.c"
#include "../importers.h"

void printStructure(Structure *structure) {
  printf("\n\n");
  printf(
    "source: %d %s:%d\n",
    structure->source.id,
    structure->source.ip,
    structure->source.port
  );
  printf(
    "destination: %d %s:%d\n",
    structure->destination.id,
    structure->destination.ip,
    structure->destination.port
  );
  printf(
    "message: %s\n",
    structure->message
  );
  printf(
    "type: %d\n",
    structure->type
  );
  printf("\n\n");
}

void printInformations() {
  int index;

  printf(
    "id: %d\n",
    information->id
  );
  printf(
    "current: %d %s:%d\n",
    information->current->id,
    information->current->ip,
    information->current->port
  );
  printf("\n");

  printf(
    "numberOfRouters: %d\n",
    information->numberOfRouters
  );
  for (index = 0; index <= information->numberOfRouters; index++)
    printf(
      "distances[%d] [%d, %d, %d] \n",
      index,
      information->distances[index].id,
      information->distances[index].src,
      information->distances[index].value
    );
  for (index = 0; index < information->numberOfRouters; index++)
    printf(
      "routerData[%d]: %d %s:%d\n",
      index,
      information->routerData[index].id,
      information->routerData[index].ip,
      information->routerData[index].port
    );
  printf("\n");

  printf(
    "numberOfConnections: %d\n",
    information->numberOfConnections
  );
  for (index = 0; index < information->numberOfConnections; index++)
    printf(
      "connectedRouters[%d]: %d -> %d\n",
      index,
      information->connectedRouters[index].id,
      information->connectedRouters[index].value
    );
  printf("\n");
}