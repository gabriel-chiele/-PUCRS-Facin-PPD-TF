#include <stdio.h>

#include "mensagem.h"

void _createMessage(/*struct contato from, struct contato to, */struct mensagem* new, char* phrase){
	/*new->de = _createContato();
	new->para = _createContato();*/
	sprintf(new->msg, "%s", phrase);
	new->estado = CRIADA;
}
