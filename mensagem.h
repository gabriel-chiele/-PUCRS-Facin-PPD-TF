#ifndef MENSAGEM_HEADER
#define MENSAGEM_HEADER

#define TAM_MAX_MSG 32

typedef struct mensagem{
	char msg[TAM_MAX_MSG];
}mensagem;

struct mensagem _createMessage(char* phrase);

#endif
