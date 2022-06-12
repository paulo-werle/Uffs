#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../data_structures.c"
#include "../functions.h"

// Função para alocar roteador
Router *allocateRouter(Router *connections, int routerId, int *connectionSize) {
  int reallocSizeOf = (*connectionSize + 1) * sizeof(Router);

  // Realoca vetor e insere novo dado
  connections = realloc(connections, reallocSizeOf);
  connections[*connectionSize].routerId = routerId;
  *connectionSize+= 1;

  return connections;
}

// Função para declarar roteadores
Router *declareRouters(Router *connections, int routerId, int *connectionSize) {
  FILE* linksFile = fopen("config/enlaces.config", "r");
  int routerX, routerY;

  if (linksFile == NULL) {
    errorMessage("declareRouters - File enlaces.config error ");
  }

  while (fscanf(linksFile, "%d %d %*d", &routerX, &routerY) == 2) {
    if (routerX == routerId) {
      connections = allocateRouter(connections, routerY, connectionSize);
    }
    if (routerY == routerId) {
      connections = allocateRouter(connections, routerX, connectionSize);
    }
  }
  fclose(linksFile);

  return connections;
}

// Função para definir as informações dos roteadores conectados
Router *setRouterInformation(Router *connections, int *connectionSize) {
  FILE* routersFile = fopen("config/roteador.config", "r");
  int routerId, port, index;
  char ip[12];

  if (routersFile == NULL) {
    errorMessage("setRouterInformation - File roteador.config error ");
  }

  // Percorre os roteadores conectados
  for (index = 0; index < *connectionSize; index++) {

    // Percorre arquivo procurando index
    while (fscanf(routersFile, "%d %d %s", &routerId, &port, ip) == 3) {
      if (connections[index].routerId == routerId) {
        connections[index].port = port;
        strcpy(connections[index].ip, ip);
      }
    }

    fseek(routersFile, 0, SEEK_SET);
  }
  fclose(routersFile);

  return connections;
}

// Função para definir as informações do roteador
Router *findCurrentRouterInformation(Router *currentRouter, int routerId) {
  FILE* routersFile = fopen("config/roteador.config", "r");
  int port, index;
  char ip[12];

  if (routersFile == NULL) {
    errorMessage("findCurrentRouterInformation - File roteador.config error ");
  }

  // Percorre arquivo procurando o roteador
  while (fscanf(routersFile, "%d %d %s", &index, &port, ip) == 3) {
    if (index == routerId) {
      currentRouter->routerId = routerId;
      currentRouter->port = port;
      strcpy(currentRouter->ip, ip);
    }
  }
  fclose(routersFile);

  return currentRouter;
}

// Função para configurar roteadores
CurrentRouterInformation *configureRouter(int routerId) {

  CurrentRouterInformation *information = malloc(sizeof(CurrentRouterInformation));

  Router *currentRouter = malloc(sizeof(Router));
  int *connectionSize = calloc(0, sizeof(int));
  Router *connections = NULL;

  // Declara roteadores que tem conexão
  connections = declareRouters(connections, routerId, connectionSize);

  // Define informações desses roteadores
  connections = setRouterInformation(connections, connectionSize);

  // Define informações do roteador atual
  currentRouter = findCurrentRouterInformation(currentRouter, routerId);

  // Atribui informações a estrutura do roteador atual
  information->connectedRouters = connections;
  information->connectedRouterSize = *connectionSize;
  information->currentRouter = currentRouter;

  return information;
}