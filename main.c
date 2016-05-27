#include <stdio.h>

#include "user.h"
#include "utils.h"

#define DEBUG

struct user usuario;
FILE* user_file;
char login[15];
char user_fileName[15];
int errn = 0;

int main(void){
	int i = 0, j = 0;
	printf("\t\t\tWhatsPPD\nUsuario:");
	gets(login);
	sprintf(user_fileName,"%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);	
		}
		#ifdef DEBUG
		else{
			printf("Name:%s\nIP:%s\nnContatos:%d\nnGrupos:%d\nContatos:\n", usuario.userName, usuario.localIP, usuario.nContatos, usuario.nGrupos);
			for(i=0;i<16;i++){
				if(i<8)
					printf("%s - ip:%s", usuario.contatos[i]._name, usuario.contatos[i]._ip);
				else
					printf("%s - ip:%s", usuario.grupos[i]._name, usuario.contatos[i]._ip);
					for(j=0;j<8;j++){
						printf("%s - ip:%s", usuario.grupos[i].contatos[j]._name, usuario.grupos[i].contatos[j]._ip);
					}
			}
		}
		#endif
	}
	else{
		createUser();
		if(!saveUser()){
			errn = 2;
			atexit(exitWithERROR);
		}
	}
	//atexit(close);
}
