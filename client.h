#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "mensagem.h"

typedef struct clientInfo{
	char host_ip[16];
	struct mensagem *msg;
}clientInfo;

int allocInfo(struct clientInfo *new, char* ip, struct mensagem* ptr);
void initClientThread(struct clientInfo* info);

#endif
