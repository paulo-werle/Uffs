#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "../data_structures.c"
#include "../functions.h"

extern CurrentRouterInformation *currentRouterInformation;

// Função para iniciar a fila
Queue *startList() {
  Queue *queue = malloc( sizeof(Queue) );
  queue = NULL;

  return queue;
}

// Função para inserir itens em uma fila
Queue *insertInTheList(Queue *queue, Structure *structure) {
  Queue *newElement = malloc( sizeof(Queue) );
	Queue *auxElement;

  // Faz apontamento para a estrutura
  newElement->structure = structure;

  // Caso a estrutura estiver vazia
  if (queue == NULL) {
    queue = newElement;

  } else {
    auxElement = queue;

    // Percorre até encontrar o ultimo elemento
    while (auxElement->next != NULL) {
      auxElement = auxElement->next;
    }
    auxElement->next = newElement;
    newElement->next = NULL;
  }

  return queue;
}

// Função para remover itens em uma fila
Queue *removeFromList(Queue *queue) {
	Queue *auxElement = queue->next;

  // Libera elemento
  free(queue);

  return auxElement;
}

// Função para gerar a estrutura
Structure *generateStructure() {
  Structure *structure = malloc(sizeof(Structure));
  int destinationRouterId;

  printf("Informa para qual vizinho se deve mandar mensagem: ");
  scanf("%d", &destinationRouterId);

  structure->destinationRouter = findConnectedRouters(destinationRouterId);
  structure->sourceRouter = currentRouterInformation->currentRouter;
  structure->messageType = 0;

  printf("Informa a mensagem que deseja mandar: ");
  scanf("%s", structure->messageLoad);

  return structure;
}