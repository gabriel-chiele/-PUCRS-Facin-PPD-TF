#include "user.h"
#include "utils.h"
#include "client.h"
#include "server.h"

struct user usuario;
FILE* user_file;
int errn = 0;
pthread_t id;
pthread_mutex_t lock;

int main(void){
	atexit(closeWHATS);
	char user_fileName[16];
	char comando, hash, blank;
	char string[1024];
	int i = 0, nArgs = 0, blank_location = 0;

	/** Login do usuario **/
	Login(user_fileName);

	/** Inicia thread do servidor **/
	printf("\n");
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
					else printf("\t\t    Comando Invalido\n");
					break;
				case 'l': // lista as msg do contato com o nome dado
					if(nArgs == 0){
						if(executeCommandList(&usuario, string)){
							printf("\t\t      Sem mensagens\n");
						}
					}
					else printf("\t\t    Comando Invalido\n");
					break;
				case 's': // envia msg para o contato com o nome dado
					if(nArgs >= 1)
						executeComandSend(&usuario, string, nArgs, user_fileName);
					else printf("\t\t    Comando Invalido\n");
					break;
				case 'c': // lista todos os contatos e grupos do usuario
					if(nArgs == 0){
						string[2] = '\0';
						printUserContacts(&usuario);
						//TODO: printUserGroups(&usuario);
					}
					break;
				default:
					printf("N funciona\n");
					break;
			}
		}
		else printf("\t\t    Comando Invalido\n");
		nArgs = 0;
		//TODO: abrir thread para tentar reenviar pendentes
	}
}
