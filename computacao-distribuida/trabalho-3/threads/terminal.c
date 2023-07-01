#include "../importers.h"

// Função: menuOptions
//   description: Responsavel por mostrar ações no menu
//   params: null
//   return: option<Int>
int menuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Oeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee \n");
  printf("2 - Exibir mensagens de dados recebidas \n");
  printf("0 - Finalizar \n");
  scanf("%d%*c", &option);

  return option;
}

// Função: scheduleMessageSending
//   description: Responsavel por agendar envio de pacote de dados
//   params: null
//   return: null
void scheduleMessageSending() {

  // Router *sendRouter = startRouter();
  // char *message = startMessage();
  // Structure *structure = generateStructure(sendRouter, message);

  // // Coloca estrutura na fila de saida
  // pthread_mutex_lock(&exitMt);
  // exitList = insertInTheList(exitList, structure);
  // pthread_mutex_unlock(&exitMt);
  // sem_post(&senderSm);
}

// Função: showMessages
//   description: Responsavel por imprimir valores da lista
//   params: list<List>
//   return: list<List>
List *showMessages(List *list) {
  printf("----------> Mensagens recebidas <----------\n");
  while (list != NULL) {
    printf("Origem: %s:%d \n", list->structure->source.ip, list->structure->source.port);
    printf("Destino: %s:%d \n", list->structure->destination.ip, list->structure->destination.port);
    printf("Mensagem: %s \n\n", list->structure->message);

    list = removeFromList(list);
  }
  printf("-------------------------------------------\n");

  return list;
}

// Função: showDataReceived
//   description: Responsavel por imprimir valores da fila de saida
//   params: null
//   return: null
void showDataReceived() {
  pthread_mutex_lock(&dataMt);
  dataList = showMessages(dataList);
  pthread_mutex_unlock(&dataMt);
}

// Função: terminalFn
//   description: Responsavel por gerenciar o terminal
//   params: null
//   return: null
void *terminalFn() {
  while (true) {
    int option = menuOptions();

    switch(option) {
      // Enviar mensagem
      case 1 :
        scheduleMessageSending();
        break;
      // Exibir mensagens de dados recebidas
      case 2 :
        showDataReceived();
        break;
      // Finalizar
      case 0 :
        exit(0);
        break;
    }
  }
}