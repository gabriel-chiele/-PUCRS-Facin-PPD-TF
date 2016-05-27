#ifndef MENSAGEM_HEADER
#define MENSAGEM_HEADER

#include "contato.h"

#define TAM_MAX_MSG 32

#define CRIADA 0
#define ENVIADA 1
#define RECEBIDA 2
#define LIDA 3

typedef struct mensagem{
	char msg[TAM_MAX_MSG];
	int estado;
	struct contato to, from;
}mensagem;

void _createMessage(struct contato* from, struct contato* to, struct mensagem* new, char* phrase);

#endif
