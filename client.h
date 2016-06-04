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

void* initClientThread(struct clientInfo info);
void* sendThread(struct mensagem *msg);

#endif