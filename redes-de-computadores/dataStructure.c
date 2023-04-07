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
  int type;
  Router source;
  Router destination;
  char message[MESSAGE_SIZE];

} Structure;

// Estrutura para Listas
typedef struct _list
{
	struct _list *next;
  Structure *structure;

} List;

// Estrutura para informações do vetor distancia
typedef struct _distance
{
  int id;
  int src;
  int value;
  time_t time;

} Distance;

// Estrutura para informações de conexões
typedef struct _connections
{
  int id;
  int value;

} Connections;

// Estrutura para informações do roteador atual
typedef struct _information
{
  int id;
  Router *current;

  int numberOfRouters;
  Distance *distances;
  Router *routerData;

  int numberOfConnections;
  Connections *connectedRouters;
} Information;