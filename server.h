#ifndef SERVER_HEADER
#define SERVER_HEADER 

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "mensagem.h"

void initServerThread(pthread_t *id);
void* handleMsg(int send_socket);
void* serverThread(void);

#endif
