#include "../dataStructure.c"
#include "../importers.h"

void sendMessage(MessageStructure *msg) {
  int lenSocket = sizeof(senderAddr);
  int code;

  senderAddr.sin_port = htons(msg->destination.port);
  if (!inet_aton(msg->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");

  code = sendto(
    sSocket, msg, sizeof(MessageStructure), 0,
    (struct sockaddr *) &senderAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

void *senderFn() {
  while(true) {
    sem_wait(&senderSm);
    sendMessage(exitList->messageStructure);

    pthread_mutex_lock(&exitMt);
    exitList = removeFromList(exitList);
    pthread_mutex_unlock(&exitMt);
  }
}