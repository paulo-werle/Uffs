#include "../importers.h"

// Função para verificar argumentos
int executionArguments(int number, char *args[]) {
  if (number != 2 || !strcmp(args[1], "--help")) {
    printf("Usage: %s <router_id> \n", args[0]);
    exit(1);
  }

  return atoi(args[1]);
}

// Função para reportar erros
void reportError(char *message) {
  perror(message);
  exit(1);
}

// Função para pegar mensagem
char *getMessage() {
  char *message = malloc(MESSAGE_SIZE);

  printf("Informe a mensagem a ser enviada: ");
  fgets(message, MESSAGE_SIZE, stdin);

  return message;
}

// Função para pegar informações de destino
Router *getDestinationInformation() {
  int index;

  printf("Para qual roteador enviaremos a mensagem?: ");
  scanf("%d%*c", &index);

  return getRouter(index);
}

// Função para buscar roteador
Router *getRouter(int id) {
  Router *router = malloc(sizeof(Router));
  int index;

  for (index = 0; index < information->numberOfRouters; index++)
    if (information->routerData[index].id == id) break;

  *router = information->routerData[index];

  return router;
}

// Função para buscar roteador apartir do vetor distancia
Router *getRouterDistance(int id) {
  int index;

  for (index = 0; index < information->numberOfRouters; index++)
    if (information->distances[index].id == id) break;

  return getRouter(information->distances[index].src);
}

// Função para gerar pacote
Structure *generateStructure(Router *router, char message[], int type) {
  Structure *structure = malloc(sizeof(Structure));

  structure->source      = *information->current;
  structure->destination = *router;
  structure->type        = type;
  strcpy(structure->message, message);

  return structure;
}