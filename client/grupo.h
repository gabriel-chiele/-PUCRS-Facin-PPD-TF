#ifndef GRUPO_HEADER
#define GRUPO_HEADER

#include <stdio.h>

#include "contato.h"

typedef struct grupo{
	char _name[9];
	char file_name[26];
	int nContatos;
	struct contato contatos[8];
}grupo;

// TODO: criar add contato em grupo já existente
void _createGrupo(struct grupo* new, char* name, struct contato* contacts, int tam);
void saveGrupo(FILE* file, struct  grupo* grupo);

#endif
