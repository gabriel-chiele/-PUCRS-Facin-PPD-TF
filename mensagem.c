#include <stdio.h>

#include "mensagem.h"

void _createTxtMessage(struct mensagem* new, char* from, char* phrase){
	new->tipo = MSG_TXT;
	sprintf(new->from, "%s", from);
	sprintf(new->msg, "%s", phrase);
	new->estado = CRIADA;
}

void _createAddContatoMessage(struct mensagem* new, char* from){
	new->tipo = ADD_CONTATO;
	sprintf(new->from, "%s", from);
	new->estado = CRIADA;
}

/* quando um grupo é criado tem q se mandar a msg de criação de grupo para todos, junto com os nome e ip 
deo participantes do grupo.

void _createAddGrupoMessage(struct mensagem* new, char* from){
	new->tipo = ADD_CONTATO;
	sprintf(new->from, "%s", from);
	new->estado = CRIADA;
}
*/
