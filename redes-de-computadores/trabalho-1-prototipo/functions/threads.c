#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>

#include "../data_structures.c"
#include "../functions.h"

#define ERROR_CODE -1

extern int routerId;
extern sem_t semaphoreForTerminal;
extern sem_t semaphoreForSending;

Queue *entryQueue;
Queue *exitQueue;

int sSocket;
struct sockaddr_in senderSocket, receiverSocket;


// Função para montar configurações de UDP
void configureUDP() {
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sSocket == ERROR_CODE) {
    errorMessage("senderFunction - Socket error\n");
  }
}

// Função para configurar socket para envio
void configureSocketToSend() {
  memset((char *) &senderSocket, 0, sizeof(senderSocket));
  senderSocket.sin_family = AF_INET;
  senderSocket.sin_port = htons(exitQueue->structure->destinationRouter->port);

  // Ajusta ip de destino
  if (!inet_aton(exitQueue->structure->destinationRouter->ip, &senderSocket.sin_addr)) {
    fprintf(stderr, "senderFunction - InetAton error\n");
    exit(1);
  }
}

// Função para configurar socket para receber
void configureSocketToReceive() {
  memset((char *) &receiverSocket, 0, sizeof(receiverSocket));
  receiverSocket.sin_family = AF_INET;
  receiverSocket.sin_port = htons(8888);
  receiverSocket.sin_addr.s_addr = htonl(INADDR_ANY);
}

// Função para mandar mensagem
void sendMessage() {
  int lenSocket = sizeof(senderSocket);

  // Envia mensagem para o destino
  if (sendto(sSocket, exitQueue->structure->messageLoad, strlen(exitQueue->structure->messageLoad), 0 , (struct sockaddr *) &senderSocket, lenSocket) == ERROR_CODE) {
    errorMessage("senderFunction - SendTo error\n");
  }

  // TODO - Implementar aguardo da resposta
}

// Função para receber mensagem
void receiveMessage() {
  int lenSocket = sizeof(senderSocket);
  int receiverLen;
  char buflen[BUFLEN];

  // Deixa disponivel para receber
  if (bind(sSocket, (struct sockaddr*)&receiverSocket, sizeof(receiverSocket) ) == ERROR_CODE) {
    errorMessage("ReceiverFunction - Bind error\n");
  }

  // TODO - Trocar while pelo conceito de mutex
  while (true) {
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

    // TODO - Implementar envio da resposta
  }
}

// Função da thread de envio
void *senderFunction() {
  configureUDP();
  while (true) {
    sem_wait(&semaphoreForSending);
    configureSocketToSend();
    sendMessage();
    sem_post(&semaphoreForTerminal);
  }
}

// Função da thread de recebimento
void *receiverFunction() {
  configureUDP();
  configureSocketToReceive();
  receiveMessage();
}

// Função da thread de manipulações de pacote
void *packetHandlerFunction() {
}

// Função da thread de terminal
void *terminalFunction() {
  while (true) {
    int option = displayMenuOptions();

    switch(option) {
      case 1 :
        Structure *structure = generateStructure();
        exitQueue = insertInTheList(exitQueue, structure);
        sem_post(&semaphoreForSending);
        sem_wait(&semaphoreForTerminal);
        exitQueue = removeFromList(exitQueue);
        break;

      case 2 :
        break;
      case 0 :
        exit(0);
        break;
    }
  }
}