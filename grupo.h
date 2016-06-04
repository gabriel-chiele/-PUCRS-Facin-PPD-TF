#ifndef GRUPO_HEADER
#define GRUPO_HEADER

#include <stdio.h>

#include "contato.h"

typedef struct grupo{
	char _name[9];
	char file_name[26];
	struct contato contatos[8];
}grupo;

void _createGrupo(struct grupo* new, char* name, struct contato* contacts, int tam);

#endif
