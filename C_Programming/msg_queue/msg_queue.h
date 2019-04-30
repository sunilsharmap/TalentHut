#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXBUFSIZE            128

#define CMD_SEND_USERNAME     0x01
#define CMD_SEND_PASSWORD     0x02

#define CMD_USERNAME_ACK      0x03
#define CMD_PASSWORD_ACK      0x04

#define CMD_CLIENT_EXIT       0x05

#define MTYPE_FROM_SERVER     0x06
#define MTYPE_FROM_CLIENT     0x07

typedef struct {
    long mtype;
    int  mcmd;
    char mtext[MAXBUFSIZE];
} msgqbuf;
