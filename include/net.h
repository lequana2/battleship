#ifndef _COMMON_NET_
#define _COMMON_NET_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdio.h>

#include "common.h"


#define BUFFER_SIZE 1024
#define HANDLER_SEND 10
#define HANDLER_SKIP 11
#define HANDLER_STOP 12


int def_server(int port, int max_connection,
               int (*handle_setup_fn)(int),
               int (*handle_client_fn)(struct sockaddr_in),
               int (*handle_message_fn)(struct sockaddr_in, char*, int, char*)) {
  int socket_desc, connection, status;
  int sin_size, recv_size;
  char recv_buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];
  struct sockaddr_in client, server;

  if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == FALSE) {
    die("socket");
  }

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  bzero(&(server.sin_zero), 8);

  if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) == FALSE) {
    die("bind");
  }

  if (listen(socket_desc, max_connection) == FALSE) {
    die("listen");
  }

  handle_setup_fn(port);
  while (TRUE) {
    connection = accept(socket_desc, (struct sockaddr*)&client, &sin_size);
    handle_client_fn(client);

    while (TRUE) {
      recv_size = recv(connection, recv_buffer, BUFFER_SIZE, 0);
      status = handle_message_fn(client, recv_buffer, recv_size, &send_buffer);

      if (status == HANDLER_STOP) {
        break;
      } else if (status == HANDLER_SEND){
        send(socket_desc, send_buffer, strlen(send_buffer), 0);
      }
    }
  }

  close(socket_desc);
  return 0;
}


int def_client(char* ip, int port,
               int (*handle_setup_fn)(struct sockaddr_in, int),
               int (*handle_message_fn)(struct sockaddr_in, char*, int, char*)) {
  int socket_desc, recv_size, status;
  char recv_buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];
  struct sockaddr_in server;

  if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == FALSE) {
    die("socket");
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (inet_pton(AF_INET, ip, &server.sin_addr) <= 0) {
    die("inet_pton");
  }

  bzero(&(server.sin_zero), 8);

  if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) == FALSE) {
    die("connect");
  }

  handle_setup_fn(server, port);
  send(socket_desc, "Hello", strlen("Hello"), 0);

  while (TRUE) {
    recv_size = recv(socket_desc, recv_buffer, BUFFER_SIZE, 0);
    recv_buffer[recv_size] = '\0';
    status = handle_message_fn(server, recv_buffer, recv_size, &send_buffer);

    if (status == HANDLER_STOP) {
      break;
    } else if (status == HANDLER_SEND){
      send(socket_desc, send_buffer, strlen(send_buffer), 0);
    }
  }

  close(socket_desc);
  return 0;
}


#endif
