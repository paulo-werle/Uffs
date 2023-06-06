#include "../importers.h"

// Função: menuOptions
//   description: Responsavel por mostrar ações no menu
//   params: null
//   return: option<Int>
int menuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Enviar operação \n");
  printf("2 - Exibir operações executadas \n");
  printf("3 - Exibir mensagens recebidas \n");
  printf("4 - Exibir confirmações recebidas \n");
  printf("5 - Exibir tempo relativo \n");
  printf("0 - Finalizar \n");
  scanf("%d%*c", &option);

  return option;
}

// Função: scheduleMessageSending
//   description: Responsavel por agendar envio de pacote de dados
//   params: null
//   return: null
void scheduleMessageSending() {
  char *message = startMessage();

  for (int index = 0; index < connections->number; index++) {
    Structure *structure = generateStructure(&connections->routers[index], message, "msg");

    // Coloca estrutura na fila de saida
    pthread_mutex_lock(&exitMt);
    exitList = insertInTheList(exitList, structure);
    pthread_mutex_unlock(&exitMt);
    sem_post(&senderSm);
  }
}

// Função: showMessages
//   description: Responsavel por imprimir valores da lista
//   params: list<List>
//   return: list<List>
List *showMessages(List *list) {
  printf("----------> Mensagens recebidas <----------\n");
  while (list != NULL) {
    printf("Origem: %s:%d      \n", list->structure->source.ip,      list->structure->source.port     );
    printf("Destino: %s:%d     \n", list->structure->destination.ip, list->structure->destination.port);
    printf("Tipo: %s           \n", list->structure->type         );
    printf("Indice: %d         \n", list->structure->index        );
    printf("Tempo relativo: %d \n", list->structure->relativeTime );
    printf("Mensagem: %s       \n", list->structure->message      );

    list = removeFromList(list);
  }
  printf("-------------------------------------------\n");

  return list;
}

// Função: showList
//   description: Responsavel por imprimir valores da fila de saida
//   params: null
//   return: null
void showList(List *list, pthread_mutex_t mt) {
  pthread_mutex_lock(&mt);
  dataList = showMessages(list);
  pthread_mutex_unlock(&mt);
}

// Função: terminalFn
//   description: Responsavel por gerenciar o terminal
//   params: null
//   return: null
void *terminalFn() {
  while (true) {
    int option = menuOptions();

    switch(option) {
      // 1 - Enviar operação
      case 1 :
        scheduleMessageSending();
        break;
      // 2 - Exibir operações executadas
      case 2 :
        showList(dataList, dataMt);
        break;
      // 3 - Exibir mensagens recebidas
      case 3 :
        showList(msgList, msgMt);
        break;
      // 4 - Exibir confirmações recebidas
      case 4 :
        showList(ackList, ackMt);
        break;
      // 5 - Exibir tempo relativo
      case 5 :
        printf("Tempo relativo: %d \n\n", relativeTime);
        break;
      // 0 - Finalizar
      case 0 :
        exit(0);
        break;
    }
  }
}