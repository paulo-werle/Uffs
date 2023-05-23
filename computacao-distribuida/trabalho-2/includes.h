#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/time.h>
#include "RouterList.h"
// --
#define MSG_PING 1
#define MSG_PONG 2
#define MSG_ELECTION 3
#define MSG_OK 4
#define MSG_COORDINATOR 5
#define MSG_TIMEOUT 6  

#define TIMEOUT 5
#define LIVENESS 3
#define CONFIG_FILE "config.txt"
// --
struct _coordination
{
    unsigned int message;
    unsigned int id; 
};
typedef struct _coordination CoordinationMessage;
// --
struct _coordinationmessagelist
{
    CoordinationMessage *msg;
    struct _coordinationmessagelist *next;
};
typedef struct _coordinationmessagelist CoordinationMessageList;

// --
void reportError(char *message);
void answersPing(int socket, int self_id); 
void requestsPing(int socket, RouterList *host, int self_id);  
CoordinationMessage* receives(int sSocket, RouterList *host, struct sockaddr_in* remote, int timeout); 
int requestsElection(int socket, int self_id, RouterList *rl);
void announcesCoordination(int socket, int self_id, RouterList* rl);
void answersOk(int socket, int id, int self_id, RouterList* rl); 
RouterList *getSmallerThanMe(int self_id, RouterList *rl); 
void addToMessageList(CoordinationMessage* cm, CoordinationMessageList* cml);
