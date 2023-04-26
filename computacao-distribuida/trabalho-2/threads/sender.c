#include "../importers.h"

// Função: sendMessage
//   description: Responsavel por fazer o envio da estrutura
//   params: null
//   return: null
void sendMessage(Structure *structure) {
  int lenSocket = sizeof(senderAddr);
  int code;

  // Configura socket para o destino
  senderAddr.sin_port = htons(structure->destination.port);
  if (!inet_aton(structure->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");

  // Envia estrutura
  code = sendto(
    sSocket, structure, sizeof(Structure), 0,
    (struct sockaddr *) &senderAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

// Função: senderFn
//   description: Responsavel por gerenciar os envios
//   params: null
//   return: null
void *senderFn() {
  while(true) {
    sem_wait(&senderSm);
    sendMessage(exitList->structure);

    pthread_mutex_lock(&exitMt);
    exitList = removeFromList(exitList);
    pthread_mutex_unlock(&exitMt);
  }
}