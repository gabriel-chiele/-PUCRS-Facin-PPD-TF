#include "utils.h"

/** Login de usuario **/
void Login(char* user_fileName){
	extern int errn;
	extern struct user usuario;
	char login[9];

	/** Leitura do nome do usuario pelo terminal **/
	printf("\t\t\tWhatsPPD\nUsuario:");
	fgets(login,sizeof(login),stdin);
	login[strlen(login)-1] = '\0'; // Adiciona caracter nulo no final do nome do usuario
	/** Verifica se usuario já existe **/
	sprintf(user_fileName,"%s.u",login);
	if(searchUser(user_fileName)){
		/** Carrega o usuario **/
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);
			return;	
		}
		sprintf(user_fileName,"Users/%s.u",login);
	}
	/** Senão cria usuario **/
	else{
		sprintf(user_fileName,"Users/%s.u",login);
		_createUser(&usuario,login);
		if(!saveUser(&usuario, user_fileName)){
			errn = 2;
			atexit(exitWithERROR);
		}
	}
}

/** Executa comando de listar mensagens de um contato **/
int executeCommandList(struct user* usuario, char* string){
	FILE* file;
	int index,i;
	char RX[40],name[9];

	memset(RX,'\0',40);

	/** Identifica o nome do contato **/
	for(i=3;i<strlen(string);i++){
		if(string[i] != '\n'){
			name[i-3] = string[i];
		}
		else{
			name[i-3] = '\0';
			break;
		}
	}
	/** Se contato existe **/
	if((index = ContactwithNameExist(usuario,name)) >=0 ){
		/** Abre o arquivo de mensagens **/
		if((file = fopen(usuario->contatos[index].file_name, "rb")) == NULL)
			return 1;
		while (fread(RX, TAM_MAX_MSG, 1, file) > 0){
			/** e escreve as mensagens no terminal **/
			printf("%s",RX);	
			memset(RX,'\0',40);

			if(feof(file)){
				break;
			}
		}
		close(file);			
	}
	/** Senão informa que contato não existe **/
	else printf("Contato inexistente\n");
	return 0;
}

/** Executa comando de inserção de contato **/
void executeComandInsertion(struct user* usuario, char* string, int nArgs, char* fileName){
	extern int errn;
	struct mensagem msg;
	struct clientInfo info;
	char name[9],ip[16];
	int blank_location = 0, i =0;

	memset(ip,'\0',sizeof(ip));
	memset(name,'\0',sizeof(name));

	/** Identifica nome e ip do contato **/
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
		/** Verifica existência de contato com este nome ou IP **/
		if( !((ContactExist(usuario,name,ip)) > -1 )){
			/** Envia mensagem de inserção de contato para o contato **/
			_createAddContatoMessage(&msg, usuario->userName);
			allocInfo(&info, ip, &msg);
			/** Se o contato permitir a inserção **/
			if(initClient(&info)){
				/** contato é adicionado **/
				AddContact(usuario, name, ip);
				if(!saveUser(usuario, fileName)){
					errn = 2;
					atexit(exitWithERROR);
				}
			}
		}
	}
	else printf("\t\t    Comando Invalido\n");
	#ifdef DEBUG
		DEBUG_printUser(usuario);
	#endif
	blank_location = 0;
}

/** Executa comando de envio de mensagem **/
void executeComandSend(struct user* usuario, char* string, int nArgs, char* fileName){
	extern int errn;
	struct mensagem msg;
	struct clientInfo info;
	char name[9], phrase[TAM_MAX_MSG], file_name[26];
	char msg_received[40];
	int blank_location = 0, i =0, loc = -1;

	FILE* msgfile;
		
	memset(name,'\0',sizeof(name));
	memset(phrase,'\0',sizeof(phrase));

	/** Identifica nome do contato e mensagem a ser enviada **/
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
		/** Verifica existencia de contato com nome dado **/
		if((loc = ContactwithNameExist(usuario, name)) >= 0){
			/** Envia mensagem de texto para o contato **/
			_createTxtMessage(&msg, usuario->userName, phrase);
			allocInfo(&info, usuario->contatos[loc]._ip, &msg);
			/** Se contato recebeu a mensagem **/
			if(initClient(&info)){
				/** Salva a mensagem enviada no arquivo de mensagens do contato **/
				sprintf(file_name,"Messages/%s.msg",msg.from);
				msgfile = fopen(file_name, "ab");
				sprintf(msg_received, "--> %s",msg.msg);
				fwrite(msg_received, sizeof(msg_received), 1, msgfile);
				fflush(msgfile);
				close(msgfile);
			}
		}
	}
	#ifdef DEBUG
		DEBUG_printUser(usuario);
	#endif
	blank_location = 0;
}

/** Método que encerra a thread do servidor **/
void closeWHATS(void){
	extern pthread_t id;
	pthread_join(id, NULL);
	system("clear");
	exitWithERROR();
}

/** Procura arquivo de usuario **/
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

/** Método de finalização do programa **/
void exitWithERROR(void){
	extern int errn;
	printf("\t\tProgram terminated\n");
	switch(errn){
		case 0:
			printf("\t      Finalized successfully\n");
			break;
		case 1:
			printf("\t\t     ERROR n:%d\n",errn);
			printf("\tUser file exist, but couldn't be opened.\n");
			break;
		case 2:
			printf("\t\t     ERROR n:%d\n",errn);
			printf("\tUser file couldn't be created for some reason.\n");
			break;
		case 3:
			printf("\t\t     ERROR n:%d\n",errn);
			printf("\t   Error connecting stream socket\n");
			break;
		case 4:
			printf("\t\t     ERROR n:%d\n",errn);
			printf("\t    Error setting sockets options\n");
			break;
		case 5:
			printf("\t\t     ERROR n:%d\n",errn);
			printf("\t   Error accepting socket connection\n");
			break;			
		default:
			printf("\tUndefined error occurred.\n\tPlease, contact developers.");
			break;
	}
}
