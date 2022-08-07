// files.c
void setInformation(int id);

// helpers.c
int executionArguments(int number, char *args[]);
void reportError(char *message);
void getMessage(char message[]);

Router *getRouterInformation();
MessageStructure *createStructure(Router *router, char message[]);

// lists.c
List *removeFromList(List *list);
List *insertInTheList(List *list, MessageStructure *msg);

// sockets.c
void startSocket();

// threads
void *receiverFn();
void *senderFn();
void *terminalFn();