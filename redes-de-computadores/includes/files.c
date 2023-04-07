#include "../importers.h"

// Função para abrir arquivos
FILE *openFile(char path[]) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    reportError("openFileError - Não foi possivel abrir o arquivo");
  }

  return file;
}

// Função para pegar dados do router
int matchRouter(Router *router, FILE *file) {
  return fscanf(
    file,
    "%d %d %s",
    &router->id,
    &router->port,
    router->ip
  );
}

// Função para pegar dados da conexão
int matchConnection(int values[], FILE *file) {
  return fscanf(
    file,
    "%d %d %d",
    &values[0],
    &values[1],
    &values[2]
  );
}

// Função para encontrar roteador
Router *fetchRouter(int id, FILE *file) {
  Router *router = malloc(sizeof(Router));

  while (matchRouter(router, file) == 3)
    if (id == router->id) break;

  fseek(file, 0, SEEK_SET);
  return router;
}

// Função para contar roteadores
int fetchNumberOfRouter(FILE *file) {
  Router *router = malloc(sizeof(Router));
  int number = 0;

  while (matchRouter(router, file) == 3)
    if (information->id != router->id) number++;

  fseek(file, 0, SEEK_SET);
  return number;
}

// Função para contar conexões
int fetchNumberOfConnections(FILE *file) {
  int values[3], number = 0;

  while (matchConnection(values, file) == 3)
    if (information->id == values[0] || information->id == values[1]) number++;

  fseek(file, 0, SEEK_SET);
  return number;
}

// Função para buscar roteadores
Router *fetchRouterData(FILE *file) {
  Router *routers = malloc(sizeof(Router) * information->numberOfRouters);
  Router *router = malloc(sizeof(Router));
  int index = 0;

  while (matchRouter(router, file) == 3)
    if (information->id != router->id)
      routers[index++] = *router;

  fseek(file, 0, SEEK_SET);
  return routers;
}

// Função para buscar roteadores conectados
Connections *fetchConnectedRouters(FILE *file) {
  Connections *connections = malloc(sizeof(Connections) * information->numberOfConnections);
  int values[3], index = 0;

  while (matchConnection(values, file) == 3) {
    if (information->id == values[0]) {
      connections[index].id    = values[1];
      connections[index].value = values[2];
      index++;
    }

    if (information->id == values[1]) {
      connections[index].id    = values[0];
      connections[index].value = values[2];
      index++;
    }
  }

  fseek(file, 0, SEEK_SET);
  return connections;
}

// Função para iniciar vetor distancia
Distance *fetchRouterDistances() {
  Distance *distances = malloc(sizeof(Distance) * (information->numberOfRouters + 1));
  int index = 0;

  distances[index].id    = information->id;
  distances[index].src   = information->id;
  distances[index].value = 0;
  distances[index].time  = 0;

  for (index = 0; index < information->numberOfRouters; index++) {
    distances[index + 1].id    = information->routerData[index].id;
    distances[index + 1].src   = information->id;
    distances[index + 1].value = INFINITE;
    distances[index + 1].time  = 0;
  }

  return distances;
}

// Função para definir informações do roteador
void setInformation(int id) {
  FILE* lFile = openFile("config/enlaces.config");
  FILE* rFile = openFile("config/roteador.config");

  information                      = malloc(sizeof(Information));
  information->id                  = id;
  information->current             = fetchRouter(id, rFile);
  information->numberOfRouters     = fetchNumberOfRouter(rFile);
  information->routerData          = fetchRouterData(rFile);
  information->numberOfConnections = fetchNumberOfConnections(lFile);
  information->connectedRouters    = fetchConnectedRouters(lFile);
  information->distances           = fetchRouterDistances();
}