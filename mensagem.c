#include <stdio.h>

#include "mensagem.h"

void _createMessage(struct contato* from, struct contato* to, struct mensagem* new, char* phrase){
	_createContato(&new->from, from->_name, from->_ip);
	_createContato(&new->to, to->_name, to->_ip);
	sprintf(new->msg, "%s", phrase);
	new->estado = CRIADA;
}
