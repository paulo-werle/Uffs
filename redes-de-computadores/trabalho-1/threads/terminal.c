#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void scheduleShipping() {
  char message[MESSAGE_SIZE];
  Router *router;

  // Obtem informações de envio
  router = getRouterInformation();
  getMessage(message);

  // Monta estrutura para envio
  MessageStructure *msg = createStructure(router, message);

  // Prepara envio
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