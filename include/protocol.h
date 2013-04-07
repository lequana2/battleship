
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define PORT 5000
#define MAX_NAME_LEN 32
#define BUFFER_SIZE 1024

typedef enum MessageType_ {
    // Test
    MSG_TEXT,

    // Client
    MSG_CONNECT, MSG_DISCONNECT,
    MSG_BEGIN, MSG_END,
    MSG_INVITE, MSG_REPLY,
    MSG_TURN, MSG_MOVE,
    MSG_LIST_PLAYERS,

    // Server
    MSG_ERROR,
    MSG_PLAYERS,
} MessageType;

typedef enum Result_ {
    WIN, LOSE
} Result;


typedef struct TextMessage_ {
    char content[BUFFER_SIZE];
} TextMessage;

typedef struct ConnectMessage_ {
    char name[MAX_NAME_LEN];
} ConnectMessage;

typedef struct PlayersMessage_ {
    int ids[20];
    char names[20][MAX_NAME_LEN];
} PlayersMessage;

typedef struct InviteMessage_ {
    int id;
} InviteMessage;

typedef struct MoveMessage_ {
    int x;
    int y;
} MoveMessage;

typedef struct EndMessage_ {
    Result result;
} EndMessage;

typedef struct Message_ {
    MessageType type;
    union {
        TextMessage text;
        ConnectMessage connect;
        PlayersMessage players;
        InviteMessage invite;
        MoveMessage move;
        EndMessage end;
        TextMessage error;
    };
} Message;

#endif
