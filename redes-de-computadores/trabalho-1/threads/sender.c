#include "../dataStructure.c"
#include "../importers.h"

void handleControlMessage(Structure *structure) {
  senderAddr.sin_port = htons(structure->destination.port);
  if (!inet_aton(structure->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");
}

void handleDataMessage(Structure *structure) {
  Router *router = getRouterDistance(structure->destination.id);

  senderAddr.sin_port = htons(router->port);
  if (!inet_aton(router->ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");
}

void sendMessage(Structure *structure) {
  int lenSocket = sizeof(senderAddr);
  int code;

  if (structure->type == CONTROL_TYPE)
    handleControlMessage(structure);

  if (structure->type == DATA_TYPE)
    handleDataMessage(structure);

  code = sendto(
    sSocket, structure, sizeof(Structure), 0,
    (struct sockaddr *) &senderAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

void *senderFn() {
  while(true) {
    sem_wait(&senderSm);
    sendMessage(exitList->structure);

    pthread_mutex_lock(&exitMt);
    exitList = removeFromList(exitList);
    pthread_mutex_unlock(&exitMt);
  }
}