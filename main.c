#include "user.h"
#include "utils.h"
#include "client.h"
#include "server.h"

#define DEBUG
//#define ADD_CONTACT

struct user usuario;
FILE* user_file;
int errn = 0;
pthread_t id;


int main(void){
	char login[9], user_fileName[16], string[1024];
	char comando, hash, blank;
	char name[9],ip[16];
	int i = 0, nArgs = 0, blank_location = 0;

	/** login do usuario **/

	printf("\t\t\tWhatsPPD\nUsuario:");
	fgets(login,sizeof(login),stdin);
	login[strlen(login)-1] = '\0'; // ADD NULL CHARACTER AT THE END OF USER NAME
	sprintf(user_fileName,"%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);
			return;	
		}
		#ifdef DEBUG
			printf("DEBUG\n");
			DEBUG_printUser(&usuario);
		#endif
	}
	else{
		sprintf(user_fileName,"Users/%s.u",login);
		_createUser(&usuario,login);
		#ifdef ADD_CONTACT
			AddContact(&usuario, "gabriel", "127.0.0.1");
		#endif
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
					if(nArgs == 1){
						for(i=3;i<strlen(string);i++){
							if(string[i] == ' '){
								blank_location = i;
							}
							else{
								if(blank_location > 0){
									ip[i-blank_location-1] = string[i];
									if(string[i] == '\n'){
										ip[i-blank_location-1] = '\0';
										break;
									}
								}
								else{
									name[i-3] = string[i];
								}
							}
						}
					}
					//TODO: verificar se contato com este nome ou ip já existe
					AddContact(&usuario, name, ip);
							#ifdef DEBUG
								DEBUG_printUser(&usuario);
							#endif
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
		atexit(close);
	#endif
}
