// --
struct _router
{
    int port;
    char ip[15];
};
typedef struct _router Router;
// --
struct _routerlist
{
    Router *host;    
    unsigned int id; 
    unsigned int threshold;
    struct _routerlist *next;
};
typedef struct _routerlist RouterList; 

// --

RouterList* generateList(char *filename);  
RouterList* getCoordinator(int coordinator_id, RouterList *list); 
//RouterList *getCoordinatorByIp(struct in_addr sin, RouterList *rl); 
int getCoordinatorId(RouterList *rl); 
void showList(RouterList *rl, char* message, int id);  
RouterList *getGreaterThanMe(int self_id, RouterList *rl); 
void addToList(RouterList* list, RouterList* rl);
char* reportMsg(int message);
int listLength(RouterList* rl);