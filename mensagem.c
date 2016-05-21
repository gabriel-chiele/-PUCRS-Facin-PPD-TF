#include <stdio.h>

#define TAM_MAX_MSG 32

struct mensagem{
	char msg[TAM_MAX_MSG];
}mensagem;

struct mensagem* _createMessage(char* phrase){
	struct mensagem *msg;
	sprintf(msg->msg, "%s", phrase);
}

void main (void){
	struct mensagem* msg;

	msg = _createMessage("teste");
	printf ("%s\n",msg->msg);
}