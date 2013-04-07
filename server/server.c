
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "config.h"
#include "net.h"
#include "protocol.h"

Message handle_connect_msg(Message msg) {
    Message res;

    return res;
}

void handler(int client) {
    int n;
    Message req, res;

    n = read(client, &req, sizeof(req));
    if (n < 0) server_error("reading from socket");

    switch (req.type) {
        case MSG_CONNECT:
            // TODO: add the name to player list, respond with MSG_SUCCESS
            res = handle_connect_msg(req);
            break;
        case MSG_LIST_PLAYERS:
            // TODO: respond with MSG_PLAYERS
            break;
        case MSG_INVITE:
            // TODO: send MSG_INVITE to the other player, respond with MSG_SUCCESS/MSG_ERROR
            break;
        case MSG_REPLY_ACCEPT:
            // TODO: send MSG_BEGIN to both the players, send MSG_TURN to one of them
            break;
        case MSG_REPLY_DENY:
            // TODO: send MSG_ERROR to the original player
            break;
        case MSG_MOVE:
            // TODO: send MSG_MOVE to the other player, respond with MSG_SUCCESS
            break;
        case MSG_END:
            // TODO: send MSG_END to both players
            break;
        case MSG_DISCONNECT:
            // TODO: delete from player list, broad cast to all other players with MSG_DISCONNECT, respond with MSG_SUCCESS
            break;
        case MSG_TEXT:
            break;
    }

    n = write(client, &res, sizeof(res));
    if (n < 0) server_error("writing to socket");
}

int main() {
    Server *server = create_server();

    server->port = PORT;
    server->handler = &handler;
    server_start(server);

    return 0;
}
