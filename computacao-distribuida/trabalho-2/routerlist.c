#include "includes.h"

RouterList *generateList(char *filename)
{
    RouterList *rl = NULL;
    char line[1024];
    char *token;
    char *tokens[10]; // maximum of 10 tokens per line
    int num_tokens;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return NULL;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp) != NULL)
    {
        num_tokens = 0;
        token = strtok(buffer, " \t\n");
        // printf("%s\n",token);
        while (token != NULL)
        {
            // trim leading and trailing whitespace from each token
            char *start = token;
            char *end = token + strlen(token) - 1;
            while (isspace(*start))
                start++;
            while (isspace(*end))
                end--;
            *(end + 1) = '\0'; // terminate the string at the end of the trimmed token
            // assign the trimmed token to the next char* variable
            tokens[num_tokens++] = start;
            token = strtok(NULL, " \t\n");
        }
        RouterList *rla = malloc(sizeof(RouterList));
        rla->host = malloc(sizeof(Router));
        strcpy(rla->host->ip, tokens[1]);
        rla->host->port = atoi(tokens[2]);
        rla->id = atoi(tokens[0]);
        rla->threshold = 0;
        rla->next = NULL;
        if (rl == NULL)
            rl = rla;
        else
            addToList(rl, rla);
    }

    // close the file
    fclose(fp);
    return rl;
}

RouterList *getCoordinator(int coordinator_id, RouterList *list)
{
    RouterList *aux = list;
    while (aux != NULL)
    {
        //printf("Testando host: %s %d %d %d\n",aux->host->ip, aux->host->port, aux->id, aux->threshold);
        if (aux->id == coordinator_id)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

RouterList *getCoordinatorByIp(struct in_addr sin, RouterList *rl)
{
    RouterList *aux = rl;
    char ip[15];
    strcpy(inet_ntoa(sin), ip);

    while (aux != NULL)
    {
        if (strcmp(ip, aux->host->ip) == 0)
        {
            return aux;
        }
        aux = aux->next;
    }
    return 0;
}

int getCoordinatorId(RouterList *rl)
{
    RouterList *aux = rl;
    int coordinatorId = 0;
    while (aux != NULL)
    {
        if (aux->id > coordinatorId)
            coordinatorId = aux->id;
        aux = aux->next;
    }

    return coordinatorId;
}

void showList(RouterList *rl, char* message, int id)
{
    RouterList* aux = rl;
    printf("%s %d", message, id);
    while (aux != NULL)
    {
        //printf("\nRouter %d %s:%d Next: %d\n", aux->id, aux->host->ip, aux->host->port, (int) aux->next);
        aux = aux->next;
    }
} 

void addToList(RouterList* list, RouterList* rl)
{
    RouterList* aux = list;
    RouterList* anterior = NULL;

    while(aux != NULL)
    {
        anterior = aux;
        aux = aux->next;
    }
    anterior->next = rl;
    rl->next = NULL;
}

RouterList *getGreaterThanMe(int self_id, RouterList *rl)
{
    RouterList *greater = NULL;
    RouterList *aux2 = NULL;
    RouterList *aux = rl;

    while (aux != NULL)
    {   
        //printf("%d", (int) &aux);
        //sleep(1);
        //printf("[DEBUG] AUX ID %d IP %s PORT %d \n", aux->id, aux->host->ip, aux->host->port);
        if (aux->id > self_id)
        {
            aux2 = malloc(sizeof(RouterList));
            memcpy(aux2, aux, sizeof(RouterList));
            //printf("[DEBUG] AUX2 ID %d IP %s PORT %d \n", aux2->id, aux2->host->ip, aux2->host->port);
            if (greater == NULL)
            {
                greater = aux2;
            }
            else
            {
                addToList(greater, aux2);
            }
            if(aux->id == aux2->id) break;
        }
        aux = aux->next;
    }
    greater->next = NULL;
    return greater;
}

RouterList *getSmallerThanMe(int self_id, RouterList *rl)
{
    RouterList *smaller = NULL;
    RouterList *aux2 = NULL;
    RouterList *aux = rl;

    while (aux != NULL)
    {
        if (aux->id < self_id)
        {
            aux2 = malloc(sizeof(RouterList));
            memcpy(aux2, aux, sizeof(RouterList));
            if (smaller == NULL)
                smaller = aux2;
            else
                addToList(smaller, aux2);
            if(aux->id == aux2->id) break;
        }
        aux = aux->next;
    }

    return smaller;
}

void addToMessageList(CoordinationMessage *cm, CoordinationMessageList *cml)
{
    CoordinationMessageList* new = malloc(sizeof(CoordinationMessageList));
    new->msg = cm;
    new->next = NULL;

    CoordinationMessageList* anterior = NULL;
    CoordinationMessageList* aux = cml;
    while (aux != NULL)
    {
        anterior = aux;
        aux = aux->next;
    }
    anterior->next = new;
}

int listLength(RouterList * rl)  
{
    int counter = 0;
    RouterList* aux = rl;
    while(aux != NULL)
    {
        counter++;
        aux = aux->next;
    }
    return counter;
}