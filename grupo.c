#include <stdio.h>
#include "grupo.h"

void _createGrupo(struct grupo* new, char* name, struct contato* contacts, int size){
	int i;
	sprintf(new->_name,"#%s",name);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);
	for (i = 0; i < size; ++i){
		_createContato(&(new->contatos[i]), contacts[i]._name, contacts[i]._ip);
	}
}


