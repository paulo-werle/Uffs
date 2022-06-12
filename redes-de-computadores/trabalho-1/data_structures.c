#define BUFLEN 512

struct _router
{
  int routerId;
  char ip[12];
	int port;
};
typedef struct _router Router;

struct _structure
{
  int messageType;
  Router *sourceRouter;
  Router *destinationRouter;
  char messageLoad[BUFLEN];
};
typedef struct _structure Structure;

struct _queue
{
  Structure *structure;
	struct _queue *next;
};
typedef struct _queue Queue;

struct _current_router_information
{
  Router *currentRouter;
  Router *connectedRouters;
  int connectedRouterSize;
};
typedef struct _current_router_information CurrentRouterInformation;
