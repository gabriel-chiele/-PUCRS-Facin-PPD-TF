#ifndef CONTATO_HEADER
#define CONTATO_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato{
	char _name[9];
	char _ip[16];
	char file_name[26];
}contato;

void _createContato(struct contato* new, char* name, char* ip);
void saveContato(FILE* file ,struct contato* contato);
void _listMsgs(struct contato* contact_list, char* name, int nContatos);

#endif

