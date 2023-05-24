// Estrutura para informações do roteador
typedef struct _router
{
  int id;
	int port;
  char ip[15];

} Router;

// Estrutura para informações da mensagem
typedef struct _structure
{
  Router source;
  Router destination;

  // Operações: dep100 || jur1% || credito
  char message[MESSAGE_SIZE];
  // Tipo: msg || ack
  char type[3];
  // Indice
  int index;
  // Tempo relativo
  int relativeTime;

} Structure;

// Estrutura para Listas
typedef struct _list
{
	struct _list *next;
  Structure *structure;

} List;

// Estrutura para informações de conexões
typedef struct _connections
{
  int number;
  Router *routers;

} Connections;
