#include "user.h"
#include "utils.h"
#include "client.h"
#include "server.h"

//#define DEBUG
//#define ADD_CONTACT

struct user usuario;
FILE* user_file;
int errn = 0;
pthread_t id;

int main(void){
	char user_fileName[16];
	char comando, hash, blank;
	char string[1024];
	int i = 0, nArgs = 0, blank_location = 0;

	Login(user_fileName);

	printf("\n");
	//TODO: uncomments live below, serverthread commented for test matters
	initServerThread(&id);
	
	/** loop para leitura de comandos **/	
	while(1){
		memset(string,'\0',sizeof(string));
		fgets(string, sizeof(string), stdin);
		hash = string[0];
		blank = string[2];
		if((hash == '#' && blank == ' ') || (hash == '#' && string [1] == 'c')){
			comando = tolower(string[1]);
			for(i=3;i<strlen(string);i++){
				if(string[i] == ' ' || string[i] == NULL){
					nArgs++;
				}
			}
			switch(comando){
				case 'i': // add contato com nome e ip dado
					executeComandInsertion(&usuario, string, nArgs, user_fileName);
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
						executeComandSend(&usuario, string, nArgs, user_fileName);
					break;
				case 'c': // lista todos os contatos e grupos do usuario
					if(nArgs == 0){
						string[2] = '\0';
						printUserContacts(&usuario);
					}
					break;
				default: // 
					printf("N funciona\n");
					break;
			}
		}
		else printf("\t\t    Comando Invalido\n");

		nArgs = 0;

		/*_createTxtMessage(&msg, usuario.userName,"msg em si")
		allocInfo(&info,"ip para onde mandar", msg);
		initClientThread(info);*/
	}

	#ifndef DEBUG
		atexit(closeWHATS);
	#endif
}
