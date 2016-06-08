#ifndef USER_HEADER
#define USER_HEADER

#include <stdio.h>
#include <string.h>

#include "grupo.h"

typedef struct user{
	char userName[9];
	char file_name[26];
	int nContatos;
	int nGrupos;
	struct contato contatos[8];
	struct grupo grupos[8];	
}user;

void _createUser(struct user* new, char* name);
int ContactwithNameExist(struct user* u, char* name);
int ContactwithNameIP(struct user* u, char* ip);
int GroupwithNameExist(struct user* u, char* name);
void AddGroup(struct user* u, char* name, struct contato* contacts, int size);
void AddContact(struct user* u, char* name, char* ip);
int loadUser(struct user *usuario, char* user_fileName);
int saveUser(struct user *usuario, char* user_fileName);

#endif

