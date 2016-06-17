#include "user.h"

/** Construtor de usuario **/
void _createUser(struct user* new, char* name){
	strcpy(new->userName, name);
	sprintf(new->file_name, "Users/%s.u", name);
	new->nContatos = 0;
	new->nGrupos = 0;
}

/** Verifica a existência de contato com o nome ou ip dados **/
int ContactExist(struct user* u, char* name, char* ip){
	int i;
	for(i=0;i<(u->nContatos);i++){
		if((!strcmp(u->contatos[i]._name,name)) || (!strcmp(u->contatos[i]._ip,ip)))
			return i;
		else continue;
	}
	return -1;
}

/** Verifica a existência de contato com o nome dado **/
int ContactwithNameExist(struct user* u, char* name){
	int i;
	for(i=0;i<(u->nContatos);i++){
		if(!strcmp(u->contatos[i]._name,name))
			return i;
		else continue;
	}
	return -1;
}

/** Verifica a existência de contato com o ip dado **/
int ContactwithIPExist(struct user* u, char* ip){
	int i;
	for(i=0;i<(u->nContatos);i++){
		if(!strcmp(u->contatos[i]._ip,ip))
			return i;
		else continue;
	}
	return -1;
}

/** Verifica a existência de grupo com o ip dado **/
int GroupwithNameExist(struct user* u, char* name){
	int i;
	for(i=0;i<(u->nGrupos);i++){
		if(!strcmp(u->grupos[i]._name,name))
			return i;
		else continue;
	}
	return -1;
}

//TODO: testar se contato está na lista de contatos, se ñ está tem q add, atualizar lista de grupos no arquivo do usuario
void AddGroup(struct user* u, char* name, struct contato* contacts, int size){
	if(u->nGrupos < 8){ 
		_createGrupo(&u->grupos[u->nGrupos], name, contacts, size);
		u->nGrupos++;
	}
	else printf("You don't have capacity to add a new group !\n");
}

/** Adiciona contato à lista de contatos do usuario **/
void AddContact(struct user* u, char* name, char* ip){
	if(u->nContatos < 8){
		_createContato(&u->contatos[u->nContatos], name, ip);
		u->nContatos++;
	}
	else printf("You don't have capacity to add a new contact !\n");
}

/** Carrega usuario de um arquivo **/
int loadUser(struct user *usuario, char* user_fileName){
	char aux[25];
	int i =0;
	snprintf(aux,sizeof(aux),"Users/%s",user_fileName);
	FILE* userfile = fopen(aux, "rb");
	if(userfile != NULL){
		fread(usuario->userName, sizeof(usuario->userName), 1, userfile);
		fread(usuario->file_name, sizeof(usuario->file_name), 1, userfile);
		fread(&usuario->nContatos, sizeof(int), 1, userfile);
		fread(&usuario->nGrupos, sizeof(int), 1, userfile);
		for(i=0;i< (usuario->nContatos + usuario->nGrupos);i++){
			if(i<usuario->nContatos)
				loadContato(userfile , &(usuario->contatos[i]));
			//else TODO: loadGrupo
		}
		
		fclose(userfile);
		return 1;
	}
	else return 0;
}

/** Salva usuario em um arquivo **/
int saveUser(struct user *usuario, char* user_fileName){
	// NOTE: Opening file with 'wb' will delete existent files
	int i = 0;
	int total = usuario->nContatos + usuario->nGrupos;
	FILE* userfile = fopen(user_fileName, "wb");
	if(userfile != NULL){
		/** save user name and filename **/
		fwrite(usuario->userName, sizeof(usuario->userName), 1, userfile);
		fwrite(usuario->file_name, sizeof(usuario->file_name), 1, userfile);
		/** save number of cantacts and number of groups **/
		fwrite(&(usuario->nContatos), sizeof(int), 1, userfile);
		fwrite(&(usuario->nGrupos), sizeof(int), 1, userfile);
		/** loop that saves contacts and gropus **/
		for(i = 0; i< total; i++){
			if(i < usuario->nContatos)
				saveContato(userfile, &(usuario->contatos[i]));
			else
				saveGrupo(userfile, &(usuario->grupos[i]));
		}
		fclose(userfile);
		return 1; 
	}
	else return 0;
}

/** Imprime o nome dos contatos e dos grupos de um usuario **/
void printUserContacts(struct user *usuario){
	int i =0, j=0;
	for(i=0; i < usuario->nContatos + usuario->nGrupos; i++){
		if(i < usuario->nContatos){
			printf("%s\n", usuario->contatos[i]._name);
		}
		else{
			printf("%s:\n", usuario->grupos[i]._name);
			for(j=0; j < usuario->nGrupos; j++){
				printf("%s - ip:%s", usuario->grupos[i].contatos[j]._name, usuario->grupos[i].contatos[j]._ip);
			}
		}
	}
	printf("\n");
}

void DEBUG_printUser(struct user *usuario){
	int i = 0, j = 0;
	printf("Name:%s\nnContatos:%d\nnGrupos:%d\n", usuario->userName, usuario->nContatos, usuario->nGrupos);
	printUserContacts(usuario);
}
