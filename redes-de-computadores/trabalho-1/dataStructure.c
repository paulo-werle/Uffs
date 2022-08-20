#include <time.h>

#define MESSAGE_SIZE 512

// Roteador
typedef struct _router
{
  int id;
	int port;
  char ip[15];

} Router;

// Estrutura para mensagens
typedef struct _structure
{
  int type;
  Router source;
  Router destination;
  char message[MESSAGE_SIZE];

} Structure;

// Lista
typedef struct _list
{
	struct _list *next;
  Structure *structure;

} List;

// Vetor distancia
typedef struct _distance
{
  int id;
  int src;
  int value;
  time_t time;

} Distance;

typedef struct _connections
{
  int id;
  int value;

} Connections;

// Informações do roteador
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

// routerDistances[NUMERO DE ROTEADORES][3]
// routerDistances[0][0] - Roteador
// routerDistances[0][1] - Src
// routerDistances[0][2] - Distancia