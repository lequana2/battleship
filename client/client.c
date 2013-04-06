
#include <stdio.h>
#include <stdlib.h>

#include "../common/config.h"
#include "../common/common.h"
#include "../common/net.h"

int handle_message_fn(struct sockaddr_in server, char* recv_buffer, int recv_len, char* send_buffer) {
  printf("RECV: %s\n", recv_buffer);
  input(send_buffer, "%s", "Message: ");

  if (strcmp(send_buffer, "q") == 0) {
    return HANDLER_STOP;
  }

  if (strlen(send_buffer) > 0) {
    return HANDLER_SEND;
  }

  return HANDLER_SKIP;
}

int handle_setup_fn(struct sockaddr_in server, int port) {
  printf("Connected to server - , port: %d.\n", port);
}

int main(int argc, char* argv[]) {
  return def_client("127.0.0.1", DEFAULT_PORT,
                    &handle_setup_fn,
                    &handle_message_fn);
}
