#include "../importers.h"

// Função: fetchRouterData
//   description: Responsavel por abrir arquivos
//   params: path <String>
//   return: file <File>
FILE *openFile(char path[]) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    reportError("openFileError - Não foi possivel abrir o arquivo");
  }

  return file;
}

// Função: fetchRouterData
//   description: Responsavel por pegar dados do router
//   params: rt <Router>, file <File>
//   return: int <Int>
int matchRouter(Router *rt, FILE *file) {
  return fscanf(
    file,
    "%d %d %s",
    &rt->id,
    &rt->port,
    rt->ip
  );
}

// Função: fetchRouterData
//   description: Responsavel por encontrar roteadores
//   params: file <File>
//   return: rts <Router>
Router *fetchRouter(FILE *file) {
  Router *rt = malloc(sizeof(Router));

  while (matchRouter(rt, file) == 3)
    if (router->id == rt->id) break;

  fseek(file, 0, SEEK_SET);
  return rt;
}

// Função: fetchRouterData
//   description: Responsavel por contar roteadores
//   params: file <File>
//   return: number <Int>
int fetchNumberOfRouter(FILE *file) {
  Router *rt = malloc(sizeof(Router));
  int number = 0;

  while (matchRouter(rt, file) == 3)
    if (router->id != rt->id) number++;

  fseek(file, 0, SEEK_SET);
  return number;
}

// Função: fetchRouterData
//   description: Responsavel por buscar roteadores
//   params: file <File>
//   return: rts <Router>
Router *fetchRouterData(FILE *file) {
  Router *rts = malloc(sizeof(Router) * connections->number);
  Router *rt = malloc(sizeof(Router));
  int index = 0;

  while (matchRouter(rt, file) == 3)
    if (router->id != rt->id)
      rts[index++] = *rt;

  fseek(file, 0, SEEK_SET);
  return rts;
}

// Função: setConnections
//   description: Responsavel por definir conexões
//   params: null
//   return: null
void setConnections() {
  FILE* rFile = openFile("config/roteador.config");

  connections = malloc(sizeof(Connections));
  connections->number = fetchNumberOfRouter(rFile);
  connections->routers = fetchRouterData(rFile);
  router = fetchRouter(rFile);
}