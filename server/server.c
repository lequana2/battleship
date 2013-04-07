
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "config.h"
#include "net.h"
#include "protocol.h"

void handler(int client) {
    char buff[BUFFER_SIZE] = "Hello, World!";
    int n;

    /* bzero(buff, BUFFER_SIZE); */
    /* n = read(client, buff, BUFFER_SIZE); */
    /* if (n < 0) server_error("reading from socket"); */

    Message msg;
    n = read(client, &msg, sizeof(msg));

    printf("%d\n", msg.type);
    printf("%s\n", msg.test_payload.message);

    n = write(client, buff, strlen(buff));
    if (n < 0) server_error("writing to socket");
}

int main(int argc, char* argv[]) {
    Server *server = create_server();
    server->port = PORT;
    server->handler = &handler;
    server_start(server);

    return 0;
}
