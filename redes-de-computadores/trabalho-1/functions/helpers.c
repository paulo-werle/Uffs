#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../data_structures.c"
#include "../functions.h"

extern CurrentRouterInformation *currentRouterInformation;

// Função para validar argumentos de inicialização
void validateArgument(int numberOfArguments, char *arguments[]) {
  if (numberOfArguments != 2 || strcmp(arguments[1], "--help" ) == 0) {
    printf("Usage: %s ROTER_ID \n", arguments[0]);
    exit(1);
  }
}

// Função para exibir uma mensagem de erro
void errorMessage(char *message) {
  perror(message);
  exit(1);
}

// Função para mostrar Menu
int displayMenuOptions() {
  int option;

  printf("Digite a opção desejada \n");
  printf("1 - Enviar mensagem \n");
  printf("2 - Exibir mensagens recebidas \n");
  printf("0 - Finalizar \n");
  scanf("%d%*c",&option);

  return option;
}

Router *findConnectedRouters(int routerId) {
  Router *router = NULL;
  int size = currentRouterInformation->connectedRouterSize;
  int index;

  for (index = 0; index <= size; index++) {
    if ( currentRouterInformation->connectedRouters[index].routerId == routerId) {
      router = &currentRouterInformation->connectedRouters[index];
    }
  }

  if (router == NULL) {
    errorMessage("findConnectedRouters - Roteador não encontrado \n");
  }

  return router;
}