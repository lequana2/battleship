
#ifndef _COMMON_NET_
#define _COMMON_NET_

#define MAX_CLIENT 32
#define BUFFER_SIZE 1024

typedef struct Server_ {
  int socket;
  int running;
  int port;
  void (*handler)(int);
} Server;

typedef struct Client_ {
  int socket;
  int running;
  int port;
  void (*handler)(char*);
} Client;

Server *create_server();
void start_server(Server *server);
void stop_server(Server *server);
void server_error(char *msg);

Client *create_client();
void connect_client(Client *client, char *hostname);
void disconnect_client(Client *client);
void client_send(Client *client, char *msg);
void client_error(char *msg);

#endif
