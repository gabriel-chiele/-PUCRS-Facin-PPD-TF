#include "utils.h"

void Login(char* user_fileName){
	extern int errn;
	extern struct user usuario;
	char login[9];

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
		sprintf(user_fileName,"Users/%s.u",login);
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
}

void executeComandInsertion(struct user* usuario, char* string, int nArgs, char* fileName){
	extern int errn;
	struct mensagem msg;
	struct clientInfo info;
	char name[9],ip[16];
	int blank_location = 0, i =0;

	memset(ip,'\0',sizeof(ip));
	memset(name,'\0',sizeof(name));

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
		if( !((ContactExist(usuario,name,ip)) > -1 )){
			AddContact(usuario, name, ip);
			if(!saveUser(usuario, fileName)){
				errn = 2;
				atexit(exitWithERROR);
			}

			_createAddContatoMessage(&msg, usuario->userName);
			allocInfo(&info, ip, &msg);
			initClientThread(&info);
		}
		else printf("Contato com este nome ou ip já existe em sua lista de contatos\n\n");
	}
	#ifdef DEBUG
		DEBUG_printUser(usuario);
	#endif
	blank_location = 0;
}

void executeComandSend(struct user* usuario, char* string, int nArgs, char* fileName){
	extern int errn;
	struct mensagem msg;
	struct clientInfo info;
	char name[9], phrase[TAM_MAX_MSG];
	int blank_location = 0, i =0, loc = -1;
	
	memset(name,'\0',sizeof(name));
	memset(phrase,'\0',sizeof(phrase));
	if(nArgs >= 1){
		for(i=3;i<strlen(string);i++){
			if(string[i] == ' ' && blank_location == 0){
				blank_location = i;
			}
			else{
				if(blank_location > 0){
					phrase[i-blank_location-1] = string[i];
					if(string[i] == '\n'){
						phrase[i-blank_location-1] = '\0';
						break;
					}
				}
				else{
					name[i-3] = string[i];
				}
			}
		}
		if((loc = ContactwithNameExist(usuario, name)) >= 0){
			_createTxtMessage(&msg, usuario->userName, phrase);
			allocInfo(&info, usuario->contatos[loc]._ip, &msg);
			initClientThread(&info);
		}
	}
	#ifdef DEBUG
		DEBUG_printUser(usuario);
	#endif
	blank_location = 0;
}

void closeWHATS(void){
	//TODO: Close client and server thread here, along with any possibly open file.
	extern pthread_t id;
	pthread_join(id, NULL);
	system("clear");
}

int searchUser(char* username){
	DIR *d;
	struct dirent *dir;
	d = opendir("Users");
	if (d){
		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,username)){
				return 1;
			}
		}
		closedir(d);
	}
	return 0;
}

void exitWithERROR(void){
	extern int errn;
	printf("\t\tProgram terminated\n\t\t     ERROR n:%d\n",errn);
	switch(errn){
		case 1:
			printf("\tUser file exist, but couldn't be opened.\n");
			break;
		case 2:
			printf("\tUser file couldn't be created for some reason.\n");
			break;
		case 3:
			printf("\tError connecting stream socket\n");
			break;
		case 4:
			printf("\t?\n");
			break;
		default:
			printf("\tUndefined error occurred.\n\tPlease, contact developers.");
			break;
	}
}
