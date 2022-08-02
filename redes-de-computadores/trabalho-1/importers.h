// threads
void *terminalFn();

// files.c
void setInformation(
  int id
);

// lists.c
List *insertInTheList(
  List *list,
  MessageStructure *msg
);

// helpers.c
void reportError(
  char *message
);

int executionArguments(
  int number,
  char *args[]
);

