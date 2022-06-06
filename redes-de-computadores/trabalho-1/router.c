#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFLEN 100
#define ERROR_CODE -1

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

Queue *insertInTheList(Queue *first, Structure *structure);
Queue *removeFromList(Queue *first);

void *packetHandlerFunction();
void *receiverFunction();
void *senderFunction();
void *terminalFunction();

void errorMessage(char *message);

int main() {
  pthread_t threadReceiver, threadSender, threadPacketHandler, threadTerminal;

  // Inicia threads para serviços
  pthread_create(&threadReceiver,      NULL, &receiverFunction,      NULL);
  pthread_create(&threadSender,        NULL, &senderFunction,        NULL);
  // pthread_create(&threadPacketHandler, NULL, &packetHandlerFunction, NULL);
  // pthread_create(&threadTerminal,      NULL, &terminalFunction,      NULL);

  // Finaliza threads
  pthread_join(threadReceiver,      NULL);
  pthread_join(threadSender,        NULL);
  // pthread_join(threadPacketHandler, NULL);
  // pthread_join(threadTerminal,      NULL);

  return 0;
}

// Função para a thread receber mensagens
void *receiverFunction() {
  // Iniciando variaveis
  struct sockaddr_in receiverSocket, senderSocket;
  int lenSocket = sizeof(senderSocket);
  int sSocket, receiverLen;
  char buflen[BUFLEN];

  // Monta socket com configurações para UDP
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sSocket == ERROR_CODE) {
    errorMessage("ReceiverFunction - Socket error\n");
  }

  // Configurações do socket
  memset((char *) &receiverSocket, 0, sizeof(receiverSocket));
  receiverSocket.sin_family = AF_INET;
  receiverSocket.sin_port = htons(8888);
  receiverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

  // Deixa disponivel para aceitar requisições
  if (bind(sSocket, (struct sockaddr*)&receiverSocket, sizeof(receiverSocket) ) == ERROR_CODE) {
    errorMessage("ReceiverFunction - Bind error\n");
  }

  while (true) {
    // Aguarda por mensagens
    printf("Waiting for data...");
    fflush(stdout);
    memset(buflen, '\0', BUFLEN);

    // Espera uma mensagem da origem
    receiverLen = recvfrom(sSocket, buflen, BUFLEN, 0, (struct sockaddr *) &senderSocket, &lenSocket);
    if (receiverLen == ERROR_CODE) {
      errorMessage("ReceiverFunction - RecvFrom error\n");
    }

    // Imprime mensagem recebida
    printf("Received packet from %s:%d\n", inet_ntoa(senderSocket.sin_addr), ntohs(senderSocket.sin_port));
    printf("Data: %s\n", buflen);

    // Envia resposta para a origem
    if (sendto(sSocket, buflen, receiverLen, 0, (struct sockaddr*) &senderSocket, lenSocket) == ERROR_CODE) {
      errorMessage("ReceiverFunction - SendTo error\n");
    }
  }
}

// Função para a thread enviar mensagens
void *senderFunction() {
  // Iniciando variaveis
  struct sockaddr_in senderSocket;
  int lenSocket = sizeof(senderSocket);
  int sSocket;
  char buflen[BUFLEN];
  char message[BUFLEN];

  // Monta socket com configurações para UDP
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sSocket == ERROR_CODE) {
    errorMessage("senderFunction - Socket error\n");
  }

  // Configurações do socket
  memset((char *) &senderSocket, 0, sizeof(senderSocket));
  senderSocket.sin_family = AF_INET;
  senderSocket.sin_port = htons(8888);

  // Ajusta ip de destino
  if (!inet_aton("127.0.0.1", &senderSocket.sin_addr)) {
    fprintf(stderr, "senderFunction - InetAton error\n");
    exit(1);
  }

  while(true) {
    // Aguarda mensagem
    printf("Enter message: ");
    scanf("%s", message);

    // Envia mensagem para o destino
    if (sendto(sSocket, message, strlen(message), 0 , (struct sockaddr *) &senderSocket, lenSocket) == ERROR_CODE) {
      errorMessage("senderFunction - SendTo error\n");
    }

    // Espera uma resposta do destino
    if (recvfrom(sSocket, buflen, BUFLEN, 0, (struct sockaddr *) &senderSocket, &lenSocket) == ERROR_CODE) {
      errorMessage("senderFunction - RecvFrom error\n");
    }

    // Imprime a resposta
    printf("%s \n", buflen);
  }
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

void errorMessage(char *message) {
  perror(message);
  exit(1);
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