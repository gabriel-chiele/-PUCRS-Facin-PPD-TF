#ifndef USER_HEADER
#define USER_HEADER

#include "grupo.h"

typedef struct user{
	char userName[8];
	char localIP[16];
	char file_name[25];
	int nContatos;
	int nGrupos;
	struct contato contatos[8];
	struct grupo grupos[8];	
}user;

void _createUser(struct user* new, char* name, char* ip);
int ContactwithNameExist(struct user* u, char* name);
int GroupwithNameExist(struct user* u, char* name);
void AddGroup(struct user* u, char* name, struct contato* contacts, int size);
void AddContact(struct user* u, char* name, char* ip);

int loadUser(); // keeping prototype to avoid compilation errors in this fase
int loadUser(struct user *usuario, char* user_fileName);
void saveUser();
void saveUser(struct user *usuario, char* user_fileName);

#endif

