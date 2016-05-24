#include <stdio.h>

#include "mensagem.h"

void _createMessage(struct mensagem* new, char* phrase){
	sprintf(new->msg, "%s", phrase);
	new->estado = CRIADA;
}
