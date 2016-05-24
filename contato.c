#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contato.h"

void _createContato(struct contato* new, char* name, char* ip){
	struct contato new;
	strcpy(new->_name, name);
	strcpy(new->_ip, ip);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);
}

void _listMsgs(struct contato* contact_list, char* name){
	int i,tam;
	tam = N_ELEMENTS(contact_list);
	for (i = 0; i < tam; ++i){
		if(!strcmp(contact_list[i]._name, name)){
			FILE* file;
			if(file = fopen (contact_list[i].file_name, "r")){
				char line[256];
				//criar uma msg no lugar da line e criar uma função de print msg
				while(!feof(file)){
					fgets (line, sizeof(line), file);
					printf("%s\n", line);
				}
			}
		}
	}
}

void _main(void){

	struct contato teste;
	_createContato(&teste,"carlos","10.10.10.10");

	printf("%s\n%s\n%s\n",teste._name,teste._ip,teste.file_name);
}
