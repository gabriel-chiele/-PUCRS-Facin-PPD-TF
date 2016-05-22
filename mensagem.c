#include <stdio.h>

#include "mensagem.h"

struct mensagem _createMessage(char* phrase){
	struct mensagem msg;
	sprintf(msg.msg, "%s", phrase);

	return msg;
}

void _main (void){
	struct mensagem msg;

	msg = _createMessage("teste");
	printf ("%s\n",msg.msg);
}
