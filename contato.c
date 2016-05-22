#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contato.h"

int _createContato(struct contato* new, char* name, char* ip){
	char file_name[25];

	new-> _name = malloc(10);
	new-> _ip   = malloc(16);
	new-> file_name = malloc(25);

	strcpy(new->_name, name);
	strcpy(new->_ip, ip);
	sprintf(new->file_name, "Messages/%s.msg", new->_name);

	return 1;
}

void _listMsgs(struct contato* contact_list, char* name){
	int i;
	for (i = 0; i < N_ELEMENTS(contact_list); ++i)
	{
		if(!strcmp(contact_list[i]._name, name)){
			FILE* file;
			if(file = fopen (contact_list[i].file_name, "r")){
				char* line;
				while(!feof(file)){
					line = readLine(myFile);
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
