#define MESSAGE_SIZE 512

// Roteador
typedef struct _router
{
  int id;
	int port;
  char ip[15];

} Router;

// Estrutura para mensagens
typedef struct _messageStructure
{
  int type;
  Router *source;
  Router *destination;
  char message[MESSAGE_SIZE];

} MessageStructure;

// Lista
typedef struct _list
{
	struct _list *next;
  MessageStructure *messageStructure;

} List;

// Informações do roteador
typedef struct Information
{
  Router *current;
  Router *connections;
  int connectionsNumber;

} Information;