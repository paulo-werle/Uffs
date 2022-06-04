#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct _structure
{
  int value;
  // messageType
  // sourceRouter
  // destinationRouter
  // messageLoad
};
typedef struct _structure Structure;

struct _queue
{
  Structure *structure;
	struct _queue *next;
};
typedef struct _queue Queue;


void *receiverFunction();
void *senderFunction();
void *packetHandlerFunction();
void *terminalFunction();

Queue *insertInTheList(Queue *first, Structure *structure);
Queue *removeFromList(Queue *first);


int main() {
  // pthread_t threadReceiver, threadSender, threadPacketHandler, threadTerminal;

  // Inicia threads para serviços
  // pthread_create(&threadReceiver,      NULL, &receiverFunction,      NULL);
  // pthread_create(&threadSender,        NULL, &senderFunction,        NULL);
  // pthread_create(&threadPacketHandler, NULL, &packetHandlerFunction, NULL);
  // pthread_create(&threadTerminal,      NULL, &terminalFunction,      NULL);

  // Finaliza threads
  // pthread_join(threadReceiver,      NULL);
  // pthread_join(threadSender,        NULL);
  // pthread_join(threadPacketHandler, NULL);
  // pthread_join(threadTerminal,      NULL);

  return 0;
}

void *receiverFunction() {
  // printf("Tread receiverFunction \n");
}

void *senderFunction() {
  printf("Tread senderFunction \n");
}

void *packetHandlerFunction() {
  printf("Tread packetHandlerFunction \n");
}

void *terminalFunction() {
  printf("Tread terminalFunction \n");
}

// Função para inserir itens em uma fila
Queue *insertInTheList(Queue *first, Structure *structure) {
  // Declarando variaveis
  Queue *newElement = malloc(sizeof(Queue));
	Queue *auxElement;

  // Define estrutura no elemento da Lista
  newElement->structure = structure;

  // Verefica se a lista está vazia
  if (first->structure == NULL) {
    first = newElement;

  } else {
    auxElement = first;

    // Procura ultimo elemento
    while (auxElement->next != NULL) {
      auxElement = auxElement->next;
    }
    auxElement->next = newElement;
    newElement->next = NULL;
  }

  return first;
}

// Função para remover itens em uma fila
Queue *removeFromList(Queue *first) {
  // Declarando variaveis para o proximo elemento
	Queue *auxElement = first->next;

  // Libera primeiro elemento
  free(first);

  return auxElement;
}


// Exemplo de manipulação da fila (usar mesma estrutura para entrada e saida)
// Queue *entryQueue = malloc(sizeof(Queue));;
// entryQueue->structure = NULL;
// Structure *structure1 = malloc(sizeof(Structure));
// structure1->value = 1;
// entryQueue = insertInTheList(entryQueue, structure1);
// Structure *structure2 = malloc(sizeof(Structure));
// structure2->value = 2;
// entryQueue = insertInTheList(entryQueue, structure2);
// entryQueue = removeFromList(entryQueue);
// printf("%d", entryQueue->structure->value);