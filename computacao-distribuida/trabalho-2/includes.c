#include "includes.h"


void answersPing(int socket, int self_id)
{
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));
    msg->id = self_id;

    struct sockaddr_in sourceInfo;
    memset((char *)&sourceInfo, 0, sizeof(sourceInfo));
    unsigned int lenSocket = sizeof(sourceInfo);

    int statusCode;

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Error");
    }

    // Recebe pacote
    statusCode = recvfrom(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&sourceInfo, &lenSocket);

    if (statusCode == -1)
        printf("answersPing - Erro ao enviar mensagem \n");
    else
    {
        if (msg->message == MSG_PING)
        {
            msg->message = MSG_PONG;
            statusCode = sendto(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&sourceInfo, lenSocket);
            printf("[PONG] Respondido a ping de %s \n", inet_ntoa(sourceInfo.sin_addr));
        }
    }
}

void requestsPing(int socket, RouterList *host, int self_id)
{
    int statusCode;
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));
    msg->message = MSG_PING;
    msg->id = self_id;

    struct sockaddr_in destinationInfo;
    memset((char *)&destinationInfo, 0, sizeof(destinationInfo));
    unsigned int lenSocket = sizeof(destinationInfo);

    destinationInfo.sin_port = htons(host->host->port);
    if (!inet_aton(host->host->ip, &destinationInfo.sin_addr))
        reportError("Socket - InetAton error\n");

    // Envia estrutura
    statusCode = sendto(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&destinationInfo, lenSocket);
    printf("[PING] Enviando ping para coordenador %s:%d\n", inet_ntoa(destinationInfo.sin_addr), host->host->port);

    if (statusCode == -1)
        reportError("sendMessage - Erro ao enviar mensagem\n");
}

CoordinationMessage* receives(int socket, RouterList *host, struct sockaddr_in *remote, int timeout)
{
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));

    struct sockaddr_in sourceInfo;
    memset((char *)&sourceInfo, 0, sizeof(sourceInfo));
    unsigned int lenSocket = sizeof(sourceInfo);

    int statusCode;
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Error");
    }

    // Recebe pacote
    statusCode = recvfrom(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&sourceInfo, &lenSocket);

    if (statusCode == -1)
    {
        perror("Error");
        msg->message = MSG_TIMEOUT;
        return msg;

    }
    else
    {
        memcpy(remote, &sourceInfo, sizeof(struct sockaddr_in));
        return msg;
    }
    return msg;
}

int requestsElection(int socket, int self_id, RouterList *rl)
{
    CoordinationMessage* answer = malloc(sizeof(CoordinationMessage));
    answer->message = MSG_TIMEOUT;
    answer->id = self_id;

    struct sockaddr_in remote;  
    struct sockaddr_in destinationInfo;
    unsigned int lenSocket = sizeof(destinationInfo);

    int statusCode;
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));
    msg->message = MSG_ELECTION;
    msg->id = self_id;

    RouterList *greater = getGreaterThanMe(self_id, rl);
    int length = listLength(greater);

    while (greater != NULL)
    {
        memset((char *)&destinationInfo, 0, sizeof(destinationInfo));
        memset((char *) &remote, 0, sizeof(remote));

        destinationInfo.sin_port = htons(greater->host->port);
        if (!inet_aton(greater->host->ip, &destinationInfo.sin_addr))
            reportError("Socket - InetAton error\n");

        // Envia estrutura
        statusCode = sendto(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&destinationInfo, lenSocket);
        printf("[ELECTION] Enviando eleição para nó %s id %d\n", inet_ntoa(destinationInfo.sin_addr), greater->id);

        if (statusCode == -1)
            reportError("sendMessage - Erro ao enviar mensagem\n");

        greater = greater->next;
    }

    return length;
}

void reportError(char *message)
{
    perror(message);
    exit(1);
}

void announcesCoordination(int socket, int self_id, RouterList *rl)
{
    int statusCode;
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));
    msg->message = MSG_COORDINATOR;
    msg->id = self_id;

    RouterList *smaller = getSmallerThanMe(self_id, rl);

    while (smaller != NULL)
    {
        struct sockaddr_in destinationInfo;
        memset((char *)&destinationInfo, 0, sizeof(destinationInfo));
        unsigned int lenSocket = sizeof(destinationInfo);

        destinationInfo.sin_port = htons(smaller->host->port);
        if (!inet_aton(smaller->host->ip, &destinationInfo.sin_addr))
            reportError("Socket - InetAton error\n");

        // Envia estrutura
        statusCode = sendto(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&destinationInfo, lenSocket);
        printf("[COORDINATION] Anunciando coordenaçao para nó %s ID %d\n", inet_ntoa(destinationInfo.sin_addr), smaller->id);

        if (statusCode == -1)
            reportError("sendMessage - Erro ao enviar mensagem\n");

        smaller = smaller->next;
    }
}

void answersOk(int socket, int self_id, int id, RouterList* rl)
{
    RouterList* destination = getCoordinator(id, rl);
    
    int statusCode;
    CoordinationMessage *msg = malloc(sizeof(CoordinationMessage));
    msg->message = MSG_OK;
    msg->id = self_id;

    struct sockaddr_in destinationInfo;
    memset((char *)&destinationInfo, 0, sizeof(destinationInfo));
    unsigned int lenSocket = sizeof(destinationInfo);

    destinationInfo.sin_port = htons(destination->host->port);
    if (!inet_aton(destination->host->ip, &destinationInfo.sin_addr))
        reportError("Socket - InetAton error\n");

    // Envia estrutura
    statusCode = sendto(socket, msg, sizeof(CoordinationMessage), 0, (struct sockaddr *)&destinationInfo, lenSocket);
    printf("[OK] Enviando OK para nó %s \n", inet_ntoa(destinationInfo.sin_addr));

    if (statusCode == -1)
        reportError("sendMessage - Erro ao enviar mensagem\n");
}

char* reportMsg(int message) 
{
    switch (message)
    {
        case MSG_PING:
            return "MSG_PING";
            break;
        case MSG_PONG:
            return "MSG_PONG";
            break;
        case MSG_ELECTION:
            return "MSG_ELECTION";
            break;
        case MSG_OK:
            return "MSG_OK";
            break;
        case MSG_COORDINATOR:
            return "MSG_COORDINATOR";
            break;
        case MSG_TIMEOUT:
            return "MSG_TIMEOUT";
            break;
        default:
            return "NULL";
            break;
    }
    return "NULL";
}  