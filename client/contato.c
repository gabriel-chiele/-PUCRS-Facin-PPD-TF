#include "contato.h"

void _createContato(struct contato* new, char* name, char* ip){
	strcpy(new->_name, name);
	strcpy(new->_ip, ip);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);
}

void saveContato(FILE* file ,struct contato* contato){
	fwrite((contato->_name), sizeof(contato->_name), 1, file);
	fwrite((contato->_ip), sizeof(contato->_ip), 1, file);
	fwrite((contato->file_name), sizeof(contato->file_name), 1, file);
}

void loadContato(FILE* file ,struct contato* contato){
	fread(contato->_name, sizeof(contato->_name), 1, file);
	fread(contato->_ip, sizeof(contato->_ip), 1, file);
	fread(contato->file_name, sizeof(contato->file_name), 1, file);
}

void _listMsgs(struct contato* contact_list, char* name, int nContatos){
	int i;
	for (i = 0; i < nContatos; ++i){
		if(!strcmp(contact_list[i]._name, name)){
			FILE* file;
			if(file = fopen (contact_list[i].file_name, "r")){
				char line[256];
				//criar uma msg no lugar da line e criar uma função de print msg
				while(!feof(file)){
					fgets (line, sizeof(line), file);
					printf("%s\n", line);
				}
				break;
			}
		}
	}
}
