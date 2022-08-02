#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dataStructure.c"
#include "../importers.h"
#define MESSAGE_SIZE 512

extern Information *information;

extern List *exitList;

int displayMenuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Enviar mensagem \n");
  printf("2 - Exibir mensagens recebidas \n");
  printf("0 - Finalizar \n");
  scanf("%d%*c", &option);

  return option;
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

MessageStructure *createStructure() {
  MessageStructure *msg = malloc( sizeof(MessageStructure) );
  int idx;

  printf("Para qual roteador enviaremos a mensagem?: ");
  scanf("%d%*c", &idx);

  msg->source = information->current;
  msg->destination = findRouter(idx);
  msg->type = 0;

  printf("Escreva a mensagem que será enviada: ");
  fgets(msg->message, MESSAGE_SIZE, stdin);

  return msg;
}

void sendMessage() {
  MessageStructure *msg = createStructure();
  exitList = insertInTheList(exitList, msg);

  // List *aux = exitList;
  // while (aux != NULL) {
  //   printf("%s \n", aux->messageStructure->message);
  //   aux = aux->next;
  // }

  // printf(
  //   "Origem: %d, Destino: %d, Mensagem: %s \n",
  //   msg->source->id,
  //   msg->destination->id,
  //   msg->message
  // );
}

void *terminalFn() {
  while (true) {
    // int option = displayMenuOptions();

    // switch(option) {
    //   case 1 :
    //     sendMessage();
    //     break;

    //   case 2 :
    //     break;

    //   case 0 :
    //     exit(0);
    //     break;
    // }
    sendMessage();
  }
}