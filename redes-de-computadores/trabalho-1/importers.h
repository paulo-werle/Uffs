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

#define MESSAGE_SIZE 100
#define INFINITE 26

#define DISCONECT_TIME 45
#define SIGNAL_TIME 15

#define CONTROL_TYPE 1
#define DATA_TYPE 0

#define ERROR_CODE -1

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
int bellManFord(char message[]);

// -- files.c
void setInformation(int id);

// -- helpers.c
Structure *generateStructure(Router *router, char message[], int type);
int executionArguments(int number, char *args[]);
Router *getDestinationInformation();
Router *getRouterDistance(int id);
void reportError(char *message);
Router *getRouter(int id);
char *getMessage();

// -- lists.c
List *removeFromList(List *list);
List *insertInTheList(List *list, Structure *structure);

// -- prints.c
void printStructure(Structure *structure);
void printInformations();

// -- sockets.c
void startSocket();

// -- signal.c
void sendSignal();

// -- threads
void *receiverFn();
void *senderFn();
void *terminalFn();
void *packetHandlerFn();
void *signalFn();