
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "net.h"

void handler(char *msg) {
    printf("Echo from server: %s\n", msg);
}

int main() {
    Client *client = create_client();
    client->port = PORT;
    client->handler = &handler;
    connect_client(client, "localhost");

    char buff[BUFFER_SIZE];
    printf("Please enter msg: ");
    bzero(buff, BUFFER_SIZE);
    fgets(buff, BUFFER_SIZE, stdin);

    client_send(client, buff);

    return 0;
}
