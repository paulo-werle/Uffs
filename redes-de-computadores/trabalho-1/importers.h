// files.c
void setInformation(int id);

// helpers.c
void reportError(char *message);
int executionArguments(int number, char *args[]);

// lists.c
List *removeFromList(List *list);
List *insertInTheList(List *list, MessageStructure *msg);

// sockets.c
void startSocket();

// threads
void *senderFn();
void *terminalFn();