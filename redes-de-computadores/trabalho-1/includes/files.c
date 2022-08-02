#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dataStructure.c"
#include "../importers.h"

extern Information *information;

FILE *openReadFile(char path[]) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    reportError("OpenReadFileError - Não foi possivel abrir o arquivo");
  }

  return file;
}

int getRouterDataInFile(Router *router, FILE *routerFile) {
  return fscanf( routerFile,
    "%d %d %s", &router->id, &router->port, router->ip
  );
}

int getRouterLinkInFile(int ids[], FILE *linksFile) {
  return fscanf( linksFile,
    "%d %d %*d", &ids[0], &ids[1]
  );
}

Router *findRouterInRouterFile(int id, FILE *routerFile) {
  Router *router = malloc( sizeof(Router) );

  while ( getRouterDataInFile(router, routerFile) == 3 )
    if (router->id == id) break;

  fseek(routerFile, 0, SEEK_SET);

  if (router->id != id)
    reportError("findRouterInRouterFile - Roteador inexistente");

  return router;
}

int numberOfRoutersConnected(int id, FILE *linksFile) {
  int ids[2], number = 0;

  while ( getRouterLinkInFile(ids, linksFile) == 2 )
    if (ids[0] == id || ids[1] == id) number++;

  fseek(linksFile, 0, SEEK_SET);
  return number;
}

Router *searchForConnectedRouters(int id, int number, FILE *routerFile, FILE *linksFile) {
  Router *connections = malloc( sizeof(Router) * number);
  int idx = 0, ids[2];

  while ( getRouterLinkInFile(ids, linksFile) == 2 ) {
    if (id == ids[0]) {
      connections[idx] = *findRouterInRouterFile(ids[1], routerFile);
      idx++;

    }
    if (id == ids[1]) {
      connections[idx] = *findRouterInRouterFile(ids[0], routerFile);
      idx++;

    }
  }

  return connections;
}

void setInformation(int id) {
  information = malloc( sizeof(Information) );
  FILE* routerFile = openReadFile("config/roteador.config");
  FILE* linksFile = openReadFile("config/enlaces.config");
  int number = numberOfRoutersConnected(id, linksFile);

  information->connectionsNumber = number;
  information->current = findRouterInRouterFile(id, routerFile);
  information->connections = searchForConnectedRouters(id, number, routerFile, linksFile);
}