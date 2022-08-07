#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../dataStructure.c"
#include "../importers.h"

// Informações do roteador
extern Information *information;

int executionArguments(int number, char *args[]) {
  if (number != 2 || !strcmp(args[1], "--help")) {
    printf("Usage: %s <router_id> \n", args[0]);
    exit(1);
  }

  return atoi(args[1]);
}

void reportError(char *message) {
  perror(message);
  exit(1);
}

void getMessage(char message[]) {
  printf("Informe a mensagem a ser enviada: ");
  fgets(message, MESSAGE_SIZE, stdin);
}

Router *findRouter(int idx) {
  Router *router = NULL;
  int idy;

  for (idy = 0; idy <= information->connectionsNumber; idy++)
    if (information->connections[idy].id == idx)
      router = &information->connections[idy];

  if (router == NULL)
    reportError("findRouter - Roteador não encontrado \n");

  return router;
}

Router *getRouterInformation() {
  int idx;
  printf("Para qual roteador enviaremos a mensagem?: ");
  scanf("%d%*c", &idx);

  return findRouter(idx);
}

MessageStructure *createStructure(Router *router, char message[]) {
  MessageStructure *msg = malloc( sizeof(MessageStructure) );
  int idx;

  msg->source = information->current;
  strcpy(msg->message, message);
  msg->destination = router;
  msg->type = 0;

  return msg;
}