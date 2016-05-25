#ifndef GRUPO_HEADER
#define GRUPO_HEADER

#include "contato.h"

typedef struct grupo{
	char _name[8];
	char file_name[25];
	struct contato contatos[8];
}grupo;

void _createGrupo(struct grupo* new, char* name, struct contato* contacts, int tam);

#endif
