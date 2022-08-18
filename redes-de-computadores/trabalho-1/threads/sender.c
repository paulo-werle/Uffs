#include "../dataStructure.c"
#include "../importers.h"

void sendMessage(Structure *structure) {
  int lenSocket = sizeof(senderAddr);
  int code;

  // TODO: Vamos ter que alterar a forma de pegar o destino
  senderAddr.sin_port = htons(structure->destination.port);
  if (!inet_aton(structure->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");

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
    // printStructure(exitList->structure);

    pthread_mutex_lock(&exitMt);
    exitList = removeFromList(exitList);
    pthread_mutex_unlock(&exitMt);
  }
}