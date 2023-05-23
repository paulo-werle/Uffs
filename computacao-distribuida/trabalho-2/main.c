#include "includes.h"

int main(int argc, char const *argv[])
{
    int self_id;
    int coordinator_id;
    CoordinationMessage* receivedMessage;

    RouterList *coordinator;
    char ip[30];
    strcpy(ip, argv[1]);
    int port = atoi(argv[2]);

    RouterList *routerList = generateList(CONFIG_FILE); 
    self_id = atoi(argv[3]);
    coordinator_id = getCoordinatorId(routerList);  
    printf("ID do coordenador: %d\n",coordinator_id);
    coordinator = getCoordinator(coordinator_id, routerList);

    int sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in local;  
    memset((char *) &local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in remote;  
    memset((char *) &remote, 0, sizeof(remote));

    int bindCode = bind(sSocket, (struct sockaddr *)&local, sizeof(local));  
    if (bindCode == -1) reportError("PrepareSocketToReceiver - bind error\n");

    while(true)
    {
        if (self_id == coordinator_id)
        {
            printf("Sou coordenador. \n");
            while(true)
            {
                answersPing(sSocket, self_id);
            }
        }
        else
        {
            while(coordinator->threshold < LIVENESS)
            {
                sleep(1);
                requestsPing(sSocket, coordinator, self_id);
                receivedMessage = receives(sSocket, coordinator, (struct sockaddr_in*)&remote, 2);
                
                switch (receivedMessage->message)
                {
                    case MSG_PONG:
                        printf("[FASE1][PONG] IP_SRC %s PORT_SRC %d\n",inet_ntoa(remote.sin_addr),remote.sin_port);
                        coordinator->threshold = 0;
                        break;
                    case MSG_ELECTION:
                        printf("[FASE1][ELECTION] IP_SRC %s PORT_SRC %d\n",inet_ntoa(remote.sin_addr),remote.sin_port);
                        coordinator->threshold = LIVENESS;
                        coordinator_id = 0;
                        answersOk(sSocket, self_id, receivedMessage->id, routerList);
                        break; 
                    case MSG_TIMEOUT: 
                        coordinator->threshold++;
                        break;
                    default:
                        break;
                }
            }
            if(receivedMessage->message == MSG_TIMEOUT)
            {
                coordinator_id = 0;
            }

            printf("ID coordenador %d\n", coordinator_id);
            
            while (coordinator_id == 0)
            {
                if(receivedMessage->message != MSG_OK && receivedMessage->message != MSG_COORDINATOR)
                {
                    printf("Solicitar eleição!\n");
                    int length = requestsElection(sSocket, self_id, routerList);                   
                    receivedMessage = receives(sSocket, NULL, &remote, (TIMEOUT - self_id) * 2);
                }
                    
                printf("Receives: %s\n", reportMsg(receivedMessage->message));

                switch (receivedMessage->message)
                {
                    case MSG_TIMEOUT:
                        printf("Anunciando coordenação\n");
                        coordinator_id = self_id;
                        announcesCoordination(sSocket, self_id, routerList);
                        break;
                    case MSG_ELECTION:
                        // Responde com OK
                        answersOk(sSocket, self_id, receivedMessage->id, routerList);
                        RouterList* greater = getGreaterThanMe(self_id, routerList);
                        // Se houver algum nó maior que eu, pedir eleição novamente
                        if(greater != NULL) 
                        {
                            int length = requestsElection(sSocket, self_id, routerList);
                        }
                        else
                        {
                            // Senão, aguardar novo coordenador 
                            printf("[ELECTION] Aguarda coordenador!\n");
                            receivedMessage = receives(sSocket, NULL, &remote, 60);
                        }
                        break; 
                    case MSG_OK:
                        // Aguarda o coordenador
                        printf("[OK] Aguarda coordenador!\n");
                        receivedMessage = receives(sSocket, NULL, &remote, 60); // Verificar se é necessário remover timeout do socket
                        printf("[OK] Received: %s \n", reportMsg(receivedMessage->message));
                        break;
                    case MSG_COORDINATOR:
                        printf("[COORDINATOR] Setup novo coordenador ID %d \n", receivedMessage->id);
                        coordinator = getCoordinator(receivedMessage->id, routerList);
                        printf("[COORDINATOR] Novo coordenador ID %d \n", coordinator->id);
                        coordinator_id = coordinator->id;
                        coordinator->threshold = 0;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return 0;
}
