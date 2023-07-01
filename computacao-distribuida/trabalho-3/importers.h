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
extern Connections *connections;
extern int relativeTime;

// -- Listas
extern List *entryList;  // Lista de entrada
extern List *exitList;   // Lista de saida
extern List *dataList;   // Lista de operações executadas
extern List *msgList;    // Lista de mensagens
extern List *ackList;    // Lista de confirmações

// -- Threads
extern pthread_t terminalTh;
extern pthread_t senderTh;
extern pthread_t receiverTh;
extern pthread_t packetHandlerTh;
extern pthread_t executorTh;
extern pthread_t ackTh;

// -- Mutexes
extern pthread_mutex_t entryMt;
extern pthread_mutex_t exitMt;
extern pthread_mutex_t dataMt;
extern pthread_mutex_t msgMt;
extern pthread_mutex_t ackMt;

// -- Semáforos
extern sem_t senderSm;
extern sem_t packetHandlerSm;
extern sem_t ackSm;
extern sem_t senderAckSm;

// -- Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

// -- files.c
// Função: setConnections
//   description: Responsavel por definir conexões
//   params: null
//   return: null
void setConnections();

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
// Função: generateMsgStructure
//   description: Responsavel por gerar a estrutura da mensagem
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateMsgStructure(Router *destination, char message[], int uuid);

// -- helpers.c
// Função: generateAckStructure
//   description: Responsavel por gerar a estrutura da confirmação
//   params: destination<Router>, message<String>
//   return: struncture<Structure>
Structure *generateAckStructure(Router *destination, Structure *structure);

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

// -- lists.c
// Função: insertOrderedInTheList
//   description: Responsavel por inserir itens na lista ordenadamente
//   params: list<List>, structure<Structure>
//   return: list<List>
List *insertOrderedInTheList(List *list, Structure *structure);

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

// -- threads
// Função: &executorFn
//   description: Responsavel por executar os processos
//   params: null
//   return: null
void *executorFn();

// Função: ackFn
//   description: Responsavel por executar as operações das mensagens confirmadas
//   params: null
//   return: null
void *ackFn();