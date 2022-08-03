#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dataStructure.c"
#include "../importers.h"
#define MESSAGE_SIZE 512

// Informações do roteador
extern Information *information;

// Mutexes
extern pthread_mutex_t exitMt;

// Listas
extern List *exitList;

// Semáforos
extern sem_t senderSm;

int menuOptions() {
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

void scheduleShipping() {
  MessageStructure *msg = createStructure();

  pthread_mutex_lock(&exitMt);
  exitList = insertInTheList(exitList, msg);

  pthread_mutex_unlock(&exitMt);
  sem_post(&senderSm);
}

void *terminalFn() {
  while (true) {
    int option = menuOptions();

    switch(option) {
      case 1 :
        scheduleShipping();
        break;

      case 2 :
        break;

      case 0 :
        exit(0);
        break;
    }
  }
}