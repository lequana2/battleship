
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define PORT 5000
#define MAX_USERNAME_LEN 12

typedef enum MessageType_ {
  AUTH, JOIN, TURN_BEGIN, TURN_END
} MessageType;

typedef struct AuthenticationMessage_ {
  char username[MAX_USERNAME_LEN];
} AuthenticationMessage;

typedef struct MoveMessage_ {
  char username[MAX_USERNAME_LEN];
} MoveMessage;

typedef struct Message_ {
  MessageType type;
  union {
    AuthenticationMessage authentication_payload;
    MoveMessage move_payload;
  };
} Message;

Message new_authentication_message(char* username);
Message new_move_message(char* name);

#endif
