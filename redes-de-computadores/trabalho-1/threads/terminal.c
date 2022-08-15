#include "../dataStructure.c"
#include "../importers.h"

int menuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Enviar mensagem \n");
  printf("2 - Exibir mensagens de dados recebidas \n");
  printf("3 - Exibir mensagens de controle recebidas \n");
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
  MessageStructure *msg = createStructure(router, message, DATA_TYPE);

  // Prepara envio
  pthread_mutex_lock(&exitMt);
  exitList = insertInTheList(exitList, msg);
  pthread_mutex_unlock(&exitMt);
  sem_post(&senderSm);
}

List *showMessages(List *list) {
  printf("----------> Mensagens recebidas <----------\n");
  while (list != NULL) {
    printf(
      "Roteador de origem: Id: %d Endereço: %s:%d \n",
      list->messageStructure->source.id,
      list->messageStructure->source.ip,
      list->messageStructure->source.port
    );
    printf(
      "Mensagem: %s \n",
      list->messageStructure->message
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

      case 0 :
        exit(0);
        break;
    }
  }
}