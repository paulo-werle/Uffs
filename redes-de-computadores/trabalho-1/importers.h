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

// Define o valor do infinito
#define INFINITE 100

// Define tempos de conexão
#define DISCONECT_TIME 45
#define SIGNAL_TIME 15

// Define tipos de mensagens
#define CONTROL_TYPE 1
#define DATA_TYPE 0

// Define valor de erro
#define ERROR_CODE -1

// Inclui arquivo com estruturas
#include "./dataStructure.c"

// ----- Variables -----
// -- Informações do roteador
extern Information *information;

// -- Listas
extern List *entryList;
extern List *exitList;
extern List *receiverList;
extern List *controlList;

// -- Threads
extern pthread_t terminalTh;
extern pthread_t senderTh;
extern pthread_t receiverTh;
extern pthread_t packetHandlerTh;
extern pthread_t signalTh;

// -- Mutexes
extern pthread_mutex_t entryMt;
extern pthread_mutex_t exitMt;
extern pthread_mutex_t receiverMt;
extern pthread_mutex_t controlMt;
extern pthread_mutex_t distanceMt;

// -- Semáforos
extern sem_t senderSm;
extern sem_t packetHandlerSm;

// -- Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

// ----- Functions -----
// -- bellManFord.c
// Função para gerenciar BellMan Ford
int bellManFord(char message[]);

// -- files.c
// Função para definir informações do roteador
void setInformation(int id);

// -- helpers.c
// Função para gerar pacote
Structure *generateStructure(Router *router, char message[], int type);

// Função para verificar argumentos
int executionArguments(int number, char *args[]);

// Função para pegar informações de destino
Router *getDestinationInformation();

// Função para buscar roteador apartir do vetor distancia
Router *getRouterDistance(int id);

// Função para reportar erros
void reportError(char *message);

// Função para buscar roteador
Router *getRouter(int id);

// Função para pegar mensagem de dados
char *getMessage();

// -- lists.c
// Função para remover item da lista
List *removeFromList(List *list);

// Função para inserir itens na lista
List *insertInTheList(List *list, Structure *structure);

// -- sockets.c
// Função para iniciar sockets
void startSocket();

// -- signal.c
// Função para mandar vetor distancia
void sendSignal();

// -- threads
void *receiverFn();
void *senderFn();
void *terminalFn();
void *packetHandlerFn();
void *signalFn();