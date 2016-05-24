#include <stdio.h>

#include "mensagem.h"

void _createMessage(struct mensagem new, char* phrase){
	sprintf(new->msg, "%s", phrase);
	new->estado = CRIADA;
}

void _main (void){
	struct mensagem msg;

	_createMessage(&msg,"teste");
	printf ("%s\n%d\n", msg.msg, msg.estado);
}
