#include "../dataStructure.c"
#include "../importers.h"

// Função para abrir arquivos
FILE *openFile(char path[]) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    reportError("openFileError - Não foi possivel abrir o arquivo");
  }

  return file;
}

// Função para pegar dados do roteador
int getDataFromRouter(Router *router, FILE *routerFile) {
  return fscanf( routerFile,
    "%d %d %s", &router->id, &router->port, router->ip
  );
}

// Função para pegar conexão do roteador
int getConnectionFromRouter(int ids[], FILE *linksFile) {
  return fscanf( linksFile,
    "%d %d %*d", &ids[0], &ids[1]
  );
}

// Função para pegar conexão do roteador
int getDistanceFromRouter(int ids[], FILE *linksFile) {
  return fscanf( linksFile,
    "%d %d %d", &ids[0], &ids[1], &ids[2]
  );
}

// Função para encontrar roteador no arquivo
Router *findRouterInFile(int id, FILE *routerFile) {
  Router *router = malloc( sizeof(Router) );

  while ( getDataFromRouter(router, routerFile) == 3 )
    if (router->id == id) break;

  fseek(routerFile, 0, SEEK_SET);

  if (router->id != id)
    reportError("findRouterInFile - Roteador inexistente");

  return router;
}

// Função para contar numero de roteadores conectados
int countNumberOfConnectedRouters(int id, FILE *linksFile) {
  int ids[2], number = 0;

  while ( getConnectionFromRouter(ids, linksFile) == 2 )
    if (ids[0] == id || ids[1] == id) number++;

  fseek(linksFile, 0, SEEK_SET);
  return number;
}

// Função para buscar roteadores conectados
Router *searchForConnectedRouters(int id, int number, FILE *routerFile, FILE *linksFile) {
  Router *connections = malloc( sizeof(Router) * number);
  int idx = 0, ids[2];

  while ( getConnectionFromRouter(ids, linksFile) == 2 ) {
    if (id == ids[0]) {
      connections[idx] = *findRouterInFile(ids[1], routerFile);
      idx++;

    }
    if (id == ids[1]) {
      connections[idx] = *findRouterInFile(ids[0], routerFile);
      idx++;

    }
  }

  fseek(linksFile, 0, SEEK_SET);
  return connections;
}

char *searchByDistanceFromRouters(int id, int number, FILE *linksFile) {
  char *dist = malloc( MESSAGE_SIZE );
  int indexes[3], size, idx = 0;

  while (getDistanceFromRouter(indexes, linksFile) == 3) {
    if (id == indexes[0]) {
      size = snprintf(&(dist[idx]), MESSAGE_SIZE, "%d-%d,", indexes[1], indexes[2]);
      idx += size;
    }
    if (id == indexes[1]) {
      size = snprintf(&(dist[idx]), MESSAGE_SIZE, "%d-%d,", indexes[0], indexes[2]);
      idx += size;
    }
  }

  return dist;
}

// Função para definir informações
void setInformation(int id) {
  FILE* routerFile = openFile("config/roteador.config");
  FILE* linksFile = openFile("config/enlaces.config");

  int number = countNumberOfConnectedRouters(id, linksFile);

  // Informações sobre o roteador
  information = malloc( sizeof(Information) );
  information->current = findRouterInFile(id, routerFile);

  // Informações sobre as conexões
  information->connectionsNumber = number;
  information->connections = searchForConnectedRouters(id, number, routerFile, linksFile);

  // Informações sobre as distancias
  information->distancesNumber = number;
  information->distances = searchByDistanceFromRouters(id, number, linksFile);
}