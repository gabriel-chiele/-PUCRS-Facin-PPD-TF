#include<stdio.h>
#include<stdlib.h>

struct contato{
	char* _name;
	char* _ip;
	FILE* msgs;
}contato;

int __initContato__(struct contato* new, char* name, char* ip){
	char file_name[25];

	new-> _name = malloc(8);
	new-> _ip   = malloc(15);
	
	strcpy(new->_name, name);
	strcpy(new->_ip, ip);
	
	sprintf(file_name, "Messages/%s.msg", new->_name);
	/* verificar funçao para abertura do arquivo*/
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

	return 1;
}

void main(void){

	struct contato teste;

	__initContato__(&teste,"carlos","10.10.10.10");

	printf("%s\n%s\n",teste._name,teste._ip);

}
