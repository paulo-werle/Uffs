#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

#include "../dataStructure.c"
#include "../importers.h"

#define MESSAGE_SIZE 512
#define ERROR_CODE -1

// // Listas
// extern List *exitList;

// // Semáforos
// extern sem_t senderSm;

// Socket
extern int sSocket;
extern struct sockaddr_in senderAddr;
extern struct sockaddr_in receiverAddr;

// void sendMessage(MessageStructure *msg) {
//   int lenSocket = sizeof(senderAddr);
//   int code;

//   senderAddr.sin_port = htons(msg->destination->port);
//   if (!inet_aton(msg->destination->ip, &senderAddr.sin_addr))
//     reportError("Socket - InetAton error\n");

//   code = sendto(
//     sSocket, msg->message, strlen(msg->message), 0,
//     (struct sockaddr *) &senderAddr, lenSocket
//   );

//   if (code == ERROR_CODE)
//     reportError("sendMessage - Erro ao enviar mensagem\n");
// }

void receiverMessage() {
  int lenSocket = sizeof(receiverAddr);
  char msg[MESSAGE_SIZE];
  int code;

  code = recvfrom(
    sSocket, msg, MESSAGE_SIZE, 0,
    (struct sockaddr *) &receiverAddr, &lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem \n");

  // printf()
  // printf(
  //   "Received packet from %s:%d\n",
  //   inet_ntoa(receiverAddr.sin_addr),
  //   ntohs(receiverAddr.sin_port)
  // );

  // printf("Data: %s\n", msg);
}

void *receiverFn() {
  // while(true) {
  //   // receiverMessage();
  //   // sem_wait(&senderSm);
  //   // sendMessage(exitList->messageStructure);
  //   // exitList = removeFromList(exitList);
  // }
}