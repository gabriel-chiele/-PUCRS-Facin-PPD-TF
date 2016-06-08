#include "user.h"
#include "utils.h"
#include "client.h"
#include "server.h"

#define DEBUG

struct user usuario;
FILE* user_file;
char login[9], user_fileName[16], string[1024];
char comando, hash, blank;
int errn = 0, i = 0, nArgs = 0;
pthread_t id;

int main(void){

	memset(&usuario,0,sizeof(struct user));
	/** login do usuario **/

	printf("\t\t\tWhatsPPD\nUsuario:");
	fgets(login,sizeof(login),stdin);
	login[strlen(login)-1] = '\0';
	sprintf(user_fileName,"Users/%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);	
		}
		#ifdef DEBUG
		else{
			DEBUG_printUser(&usuario);
		}
		#endif
	}
	else{
		_createUser(&usuario,login);
		AddContact(&usuario, "gabriel", "127.0.0.1");
		#ifdef DEBUG
			DEBUG_printUser(&usuario);
		#endif
		if(!saveUser(&usuario, user_fileName)){
			errn = 2;
			atexit(exitWithERROR);
		}
	}

	printf("\n");
	initServerThread(&id);
	
	/** loop para leitura de comandos **/	

	while(1){
		fgets(string, sizeof(string), stdin);
		hash = string[0];
		blank = string[2];
		if(hash == '#' && blank == ' '){
			comando = tolower(string[1]);
			for(i=3;i<strlen(string);i++){
				if(string[i] == ' ' || string[i] == NULL){
					nArgs++;
				}
			}
			switch(comando){
				case 'i': // add contato com nome e ip dado
					printf("%d",nArgs);
					if(nArgs == 1)
						printf("Funciona\n");
					break;
				case 'g': // add grupo com os nomes dados
					if(nArgs >= 2)
						printf("Funciona\n");
					break;
				case 'l': // lista as msg do contato com o nome dado
					if((strlen(string) <= 4) && (nArgs == 0))
						printf("Funciona\n");
					break;
				case 's': // envia msg para o contato com o nome dado
					if(nArgs >= 1)
						printf("Funciona\n");
					break;
				case 'c': // lista todos os contatos e grupos do usuario
					if(strlen(string) <= 4)
						printf("Funciona\n");
					break;
				default: // 
					printf("N funciona\n");
					break;
			}
		}
		else printf("\t\t    Comando Invalido\n");

/*		_createTxtMessage(&msg, usuario.userName,"msg em si")
		allocInfo(&info,"ip para onde mandar", msg);
		initClientThread(info);*/
	}

	#ifndef DEBUG
		atexit(close);
	#endif
}
