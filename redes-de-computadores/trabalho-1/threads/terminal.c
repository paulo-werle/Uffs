#include "../dataStructure.c"
#include "../importers.h"

int menuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Enviar mensagem \n");
  printf("2 - Exibir mensagens de dados recebidas \n");
  printf("3 - Exibir mensagens de controle recebidas \n");
  printf("4 - Exibir vetor distancia \n");
  printf("0 - Finalizar \n");
  scanf("%d%*c", &option);

  return option;
}

void scheduleShipping() {
  Structure *structure;
  Router *router;
  char *message;

  router = getDestinationInformation();
  message = getMessage();
  structure= generateStructure(router, message, DATA_TYPE);

  pthread_mutex_lock(&exitMt);
  exitList = insertInTheList(exitList, structure);
  pthread_mutex_unlock(&exitMt);
  sem_post(&senderSm);
}

List *showMessages(List *list) {
  printf("----------> Mensagens recebidas <----------\n");
  while (list != NULL) {
    printf(
      "Roteador de origem: Id: %d Endereço: %s:%d \n",
      list->structure->source.id,
      list->structure->source.ip,
      list->structure->source.port
    );
    printf(
      "Roteador de destino: Id: %d Endereço: %s:%d \n",
      list->structure->destination.id,
      list->structure->destination.ip,
      list->structure->destination.port
    );
    printf(
      "Mensagem: %s \n\n",
      list->structure->message
    );

    list = removeFromList(list);
  }
  printf("-------------------------------------------\n");

  return list;
}

void showDataReceived() {
  pthread_mutex_lock(&receiverMt);
  receiverList = showMessages(receiverList);
  pthread_mutex_unlock(&receiverMt);
}

void showControlReceived() {
  pthread_mutex_lock(&controlMt);
  controlList = showMessages(controlList);
  pthread_mutex_unlock(&controlMt);
}

void showDistances() {
  int index;

  pthread_mutex_lock(&distanceMt);
  printf("----------> Vetor Distancia <----------\n");
  for (index = 0; index <= information->numberOfRouters; index++) {
    printf(
      "Id: %d, Caminho: %d, Valor: %d, Tempo: %ld \n",
      information->distances[index].id,
      information->distances[index].src,
      information->distances[index].value,
      information->distances[index].time
    );
  }
  printf("---------------------------------------\n");
  pthread_mutex_unlock(&distanceMt);
}

void *terminalFn() {
  while (true) {
    int option = menuOptions();

    switch(option) {
      case 1 :
        scheduleShipping();
        break;

      case 2 :
        showDataReceived();
        break;

      case 3 :
        showControlReceived();
        break;

      case 4 :
        showDistances();
        break;

      case 0 :
        exit(0);
        break;
    }
  }
}