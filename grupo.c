#include "grupo.h"

void _createGrupo(struct grupo* new, char* name, struct contato* contacts, int size){
	int i;
	sprintf(new->_name,"#%s",name);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);
	for (i = 0; i < size; ++i){
		_createContato(&(new->contatos[i]), contacts[i]._name, contacts[i]._ip);
	}
	new->nContatos = size;
}

void saveGrupo(FILE* file, struct  grupo* grupo){
	int i;
	fwrite((grupo->_name), sizeof(grupo->_name), 1, file);
	fwrite((grupo->file_name), sizeof(grupo->file_name), 1, file);
	for(i = 0; i< grupo->nContatos; i++){
		saveContato(file, &(grupo->contatos[i]));
	}
}
