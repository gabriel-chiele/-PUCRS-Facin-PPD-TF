#include <stdio.h>
#include <string.h>
#include "user.h"

void _createUser(struct user* new, char* name){
	strcpy(new->userName, name);
	sprintf(new->file_name, "Users/%s.u", name);
	new->nContatos = 0;
	new->nGrupos = 0;
}

int ContactwithNameExist(struct user* u, char* name){
	int i;
	for(i=0;i<(u->nContatos);i++){
		if(!strcmp(u->contatos->_name,name))
			return 1;
		else continue;
	}
	return 0;
}

int ContactwithNameIP(struct user* u, char* ip){
	int i;
	for(i=0;i<(u->nContatos);i++){
		if(!strcmp(u->contatos->_ip,ip))
			return 1;
		else continue;
	}
	return 0;
}

int GroupwithNameExist(struct user* u, char* name){
	int i;
	for(i=0;i<(u->nGrupos);i++){
		if(!strcmp(u->grupos->_name,name))
			return 1;
		else continue;
	}
	return 0;
}

//TODO: testar se contato está na lista de contatos, se ñ está tem q add, atualizar lista de grupos no arquivo do usuario
void AddGroup(struct user* u, char* name, struct contato* contacts, int size){
	if(u->nGrupos < 8){ 
		_createGrupo(&u->grupos[u->nGrupos], name, contacts, size);
		u->nGrupos++;
	}
	else printf("You don't have capacity to add a new group !");
}

//TODO: testar se contato está na lista de contatos, se não estiver cria o contato, senão não faz nada
void AddContact(struct user* u, char* name, char* ip){
	if(u->nContatos < 8){
		_createContato(&u->contatos[u->nContatos], name, ip);
		u->nContatos++;
	}
	else printf("You don't have capacity to add a new contact !");
}

int loadUser(struct user *usuario, char* user_fileName){
	FILE* userfile = fopen(user_fileName, "rb");
	if(userfile != NULL){
		fread(usuario, sizeof(struct user), 1, userfile);
		fclose(userfile);
		return 1;
	}
	else return 0;
}

int saveUser(struct user *usuario, char* user_fileName){
	// TODO: add a case where the file already exist then delete the existing one and re-save the file,\
	   just to avoid the need to append.
	FILE* userfile = fopen(user_fileName, "wb");
	if(userfile != NULL){
		fwrite(usuario, sizeof(struct user), 1, userfile);
		fclose(userfile);
		return 1; 
	}
	else return 0;
}

void DEBUG_printUser(struct user *usuario){
	int i = 0, j = 0;
	printf("Name:%s\nnContatos:%d\nnGrupos:%d\n", usuario->userName, usuario->nContatos, usuario->nGrupos);
	for(i=0; i < usuario->nContatos + usuario->nGrupos; i++){
		if(i < usuario->nContatos)
			printf("%s\n", usuario->contatos[i]._name);
		else{
			printf("%s:\n", usuario->grupos[i]._name);
			for(j=0; j < usuario->nGrupos; j++){
				printf("%s - ip:%s", usuario->grupos[i].contatos[j]._name, usuario->grupos[i].contatos[j]._ip);
			}
		}
	}
}
