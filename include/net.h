
#ifndef _COMMON_NET_
#define _COMMON_NET_

#define BUFFER_SIZE 1024
#define MAX_CLIENT 32

typedef struct Server_ {
  int socket;
  int running;
  int port;
  void (*handler)(int);
} Server;

typedef struct Client_ {
  int socket;
  int running;
  void (*handler)(int);
} Client;

Server* create_server(void (*handle)(int));
void start_server(Server* server);
void stop_server(Server* server);

Client* create_client(void (*handle)(int));
void start_client(Client* client);
void stop_client(Client* client);

#endif
