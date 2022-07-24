// functions/files.c
CurrentRouterInformation *configureRouter(
  int routerId
);

// functions/queue.c
Queue *insertInTheList(
  Queue *queue, Structure *structure
);
Queue *removeFromList(
  Queue *queue
);
Queue *startList();
Structure *generateStructure();

// functions/helpers.c
Router *findConnectedRouters(
  int routerId
);
void errorMessage(
  char *message
);
void validateArgument(
  int numberOfArguments, char *arguments[]
);
int displayMenuOptions();

// functions/threads.c
void *packetHandlerFunction();
void *receiverFunction();
void *senderFunction();
void *terminalFunction();