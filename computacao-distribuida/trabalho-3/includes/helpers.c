#include "../importers.h"

// Função: handleRouter
//   description: Responsavel por montar um roteador
//   params: id<String>
//   return: router<Router>
Router *handleRouter(char id[]) {

  Router *router = malloc(sizeof(Router));
  router->id = atoi(id);

  return router;
}

// Função: handleArguments
//   description: Responsavel por lidar com os argumentos
//   params: number<Int>, args<String>
//   return: router<Router>
Router *handleArguments(int number, char *args[]) {

  if (number != 2 || !strcmp(args[1], "--help")) {
    printf("Usage: %s <router_id> \n", args[0]);
    exit(1);
  }

  return handleRouter(args[1]);
}

// Função: startMessage
//   description: Responsavel por pegar a mensagem
//   params: nul
//   return: message<String>
char *startMessage() {

  char *message = malloc(MESSAGE_SIZE);

  printf("Informe a operação a ser realizada: ");
  fgets(message, MESSAGE_SIZE, stdin);

  return message;
}

// Função: generateStructure
//   description: Responsavel por gerar a estrutura de dados
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateStructure(Router *destination, char message[], char type[]) {
  Structure *structure = malloc(sizeof(Structure));

  // Dados
  structure->source = *router;
  structure->destination = *destination;
  strcpy(structure->message, message);

  // Configurações
  strcpy(structure->type, type);
  structure->index = router->id;
  structure->relativeTime = relativeTime;

  return structure;
}

// Função: reportError
//   description: Responsavel por reportar os erros
//   params: message<String>
//   return: null
void reportError(char *message) {
  perror(message);
  exit(1);
}
