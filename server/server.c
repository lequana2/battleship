
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "config.h"
#include "net.h"

void handler(int socket) {
    char buff[BUFFER_SIZE];
    int n;

    bzero(buff, BUFFER_SIZE);
    n = read(socket, buff, BUFFER_SIZE);
    if (n < 0) server_error("reading from socket");

    printf("%s\n", buff);

    n = write(socket, buff, strlen(buff));
    if (n < 0) server_error("writing to socket");
}

int main(int argc, char* argv[]) {
    Server *server = create_server();
    server->port = PORT;
    server->handler = &handler;
    server_start(server);

    return 0;
}
