#ifndef MENSAGEM_HEADER
#define MENSAGEM_HEADER

#define TAM_MAX_MSG 32

#define CRIADA 0
#define ENVIADA 1
#define RECEBIDA 2
#define LIDA 3

typedef struct mensagem{
	char msg[TAM_MAX_MSG];
	int estado;
}mensagem;

struct mensagem _createMessage(char* phrase);

#endif
