#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

// ----- Configurações -----
// Define o tamanho da mensagem
#define MESSAGE_SIZE 100

// Define valor de erro
#define ERROR_CODE -1

// Inclui arquivo com estruturas
#include "./dataStructure.c"

// ----- Variables -----
// -- Informações do roteador
extern Router *router;

// -- Listas
extern List *entryList;
extern List *exitList;
extern List *dataList;

// -- Threads
extern pthread_t terminalTh;
extern pthread_t senderTh;
extern pthread_t receiverTh;
extern pthread_t packetHandlerTh;
// extern pthread_t signalTh;

// -- Mutexes
extern pthread_mutex_t entryMt;
extern pthread_mutex_t exitMt;
extern pthread_mutex_t dataMt;

// -- Semáforos
extern sem_t senderSm;
extern sem_t packetHandlerSm;

// -- Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

// -- helpers.c
// Função: handleArguments
//   description: Responsavel por lidar com os argumentos
//   params: number<Int>, args<String>
//   return: router<Router>
Router *handleArguments(int number, char *args[]);

// -- helpers.c
// Função: startMessage
//   description: Responsavel por pegar a mensagem
//   params: nul
//   return: message<String>
char *startMessage();

// -- helpers.c
// Função: generateStructure
//   description: Responsavel por gerar a estrutura de dados
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateStructure(Router *destination, char message[]);

// -- helpers.c
// Função: reportError
//   description: Responsavel por reportar os erros
//   params: message<String>
//   return: null
void reportError(char *message);

// -- lists.c
// Função: removeFromList
//   description: Responsavel por remover item da lista
//   params: list<List>
//   return: list<List>
List *removeFromList(List *list);

// -- lists.c
// Função: insertInTheList
//   description: Responsavel por inserir itens na lista
//   params: list<List>, structure<Structure>
//   return: list<List>
List *insertInTheList(List *list, Structure *structure);

// -- sockets.c
// Função: startSocket
//   description: Responsavel por iniciar os sockets
//   params: null
//   return: null
void startSocket();

// -- threads
// Função: receiverFn
//   description: Responsavel por gerenciar o recebimento
//   params: null
//   return: null
void *receiverFn();

// -- threads
// Função: senderFn
//   description: Responsavel por gerenciar os envios
//   params: null
//   return: null
void *senderFn();

// -- threads
// Função: terminalFn
//   description: Responsavel por gerenciar o terminal
//   params: null
//   return: null
void *terminalFn();

// -- threads
// Função: packetHandlerFn
//   description: Responsavel por gerenciar os pacotes recebidos
//   params: null
//   return: null
void *packetHandlerFn();