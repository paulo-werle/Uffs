#include "../importers.h"

// Função para configurar socket para vizinho de destino
void handleControlMessage(Structure *structure) {
  senderAddr.sin_port = htons(structure->destination.port);
  if (!inet_aton(structure->destination.ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");
}

// Função para configurar socket para viznho com menor distancia
void handleDataMessage(Structure *structure) {
  Router *router = getRouterDistance(structure->destination.id);

  senderAddr.sin_port = htons(router->port);
  if (!inet_aton(router->ip, &senderAddr.sin_addr))
    reportError("Socket - InetAton error\n");
}

// Função para fazer o envio das mensagens
void sendMessage(Structure *structure) {
  int lenSocket = sizeof(senderAddr);
  int code;

  // Configura socket para o destino
  if (structure->type == CONTROL_TYPE)
    handleControlMessage(structure);
  if (structure->type == DATA_TYPE)
    handleDataMessage(structure);

  // Envia estrutura
  code = sendto(
    sSocket, structure, sizeof(Structure), 0,
    (struct sockaddr *) &senderAddr, lenSocket
  );

  if (code == ERROR_CODE)
    reportError("sendMessage - Erro ao enviar mensagem\n");
}

// Função para gerenciar envios
void *senderFn() {
  while(true) {
    sem_wait(&senderSm);
    sendMessage(exitList->structure);

    pthread_mutex_lock(&exitMt);
    exitList = removeFromList(exitList);
    pthread_mutex_unlock(&exitMt);
  }
}