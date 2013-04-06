
#include <stdio.h>
#include <stdlib.h>

#include "../common/config.h"
#include "../common/common.h"
#include "../common/net.h"

int handle_message_fn(struct sockaddr_in client, char* recv_buffer, int recv_len, char* send_buffer) {
  printf("RECV: %s\n", recv_buffer);

  if (strcmp(recv_buffer, "q") == 0) {
    return HANDLER_STOP;
  }

  return HANDLER_SKIP;
}

int handle_setup_fn(int port) {
  printf("Server listening on port %d.\n", port);
}

int handle_client_fn(struct sockaddr_in client) {
  printf("Client connected");
}

int main(int argc, char* argv[]) {
  return def_server(DEFAULT_PORT, 5,
                    &handle_setup_fn,
                    &handle_client_fn,
                    &handle_message_fn);
}
