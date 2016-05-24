#include <stdio.h>
#include "grupo.h"

void _createGrupo(struct grupo* new, char* name, struct contato* contacts){
	sprintf(new->_name,"#%s",name);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);

	int tam = N_ELEMENTS(contacts);
	int i;
	for (i = 0; i < tam; ++i){
		_createContato(&(new->contatos[i]), contacts->_name,contacts->_ip);
	}
}


