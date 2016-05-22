#include <stdio.h>
#include <stdlib.h>

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

void _main(void){

	struct contato teste;
	_createContato(&teste,"carlos","10.10.10.10");

	printf("%s\n%s\n%s\n",teste._name,teste._ip,teste.file_name);

}

/*	
    sprintf(file_name, "Messages/%s.msg", new->_name);
	if(new->msgs = fopen (file_name, "r+")){
		fseek(new->msgs,0,SEEK_END);
		if(feof(new->msgs)){
			printf("!!!!!!");	
			fprintf(new->msgs,"!!");
			}
	}
	else{
		system("mkdir Messages");	
		new->msgs = fopen (file_name, "a+");
	}
*/
