// Estrutura para informações do roteador
typedef struct _router
{
	int port;
  char ip[15];

} Router;

// Estrutura para informações da mensagem
typedef struct _structure
{
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
