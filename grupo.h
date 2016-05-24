#ifndef GRUPO_HEADER
#define GRUPO_HEADER

#include "contato.h"

#define N_ELEMENTS(c)  (sizeof(c) / sizeof((c)[0]))

typedef struct grupo{
	char _name[9];
	char file_name[25];
	struct contato contatos[8];
}grupo;

void _createGrupo(struct grupo* new, char* name, struct contato* contacts);

#endif
