#include <stdio.h>

#include "mensagem.h"

struct mensagem _createMessage(char* phrase){
	struct mensagem msg;
	sprintf(msg.msg, "%s", phrase);
	msg.estado = CRIADA;

	return msg;
}

void main (void){
	struct mensagem msg;

	msg = _createMessage("teste");
	printf ("%s\n%d\n", msg.msg, msg.estado);
}
