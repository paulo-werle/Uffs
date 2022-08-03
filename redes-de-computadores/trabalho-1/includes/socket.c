#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "../dataStructure.c"
#include "../importers.h"

#define ERROR_CODE -1

// Informações do roteador
extern Information *information;

// Socket
extern int sSocket;
extern struct sockaddr_in socketAddr;

void startSocket() {
  sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sSocket == ERROR_CODE)
    reportError("Socket - sSocket error\n");

  memset((char *) &socketAddr, 0, sizeof(socketAddr));
  socketAddr.sin_family = AF_INET;
  socketAddr.sin_port = htons(information->current->port);
  socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (!inet_aton(information->current->ip, &socketAddr.sin_addr))
    reportError("Socket - InetAton error\n");
}