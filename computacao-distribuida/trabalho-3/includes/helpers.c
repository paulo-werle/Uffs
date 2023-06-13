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

// Função: generateMsgStructure
//   description: Responsavel por gerar a estrutura da mensagem
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateMsgStructure(Router *destination, char message[], int uuid) {
  Structure *structure = malloc(sizeof(Structure));

  // Dados
  structure->source = *router;
  structure->destination = *destination;
  strcpy(structure->message, message);

  // Configurações
  structure->uuid = uuid;
  strcpy(structure->type, "msg");
  structure->index = router->id;
  structure->relativeTime = relativeTime;

  return structure;
}

// Função: generateAckStructure
//   description: Responsavel por gerar a estrutura da confirmação
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateAckStructure(Router *destination, Structure *structure) {
  Structure *newStructure = malloc(sizeof(Structure));

  // Dados
  newStructure->source = *router;
  newStructure->destination = *destination;
  strcpy(newStructure->message, structure->message);

  // Configurações
  strcpy(newStructure->type, "ack");
  newStructure->uuid = structure->uuid;
  newStructure->index = structure->index;
  newStructure->relativeTime = structure->relativeTime;

  return newStructure;
}

// Função: reportError
//   description: Responsavel por reportar os erros
//   params: message<String>
//   return: null
void reportError(char *message) {
  perror(message);
  exit(1);
}
