#include "grupo.h"

typedef struct user{
	char userName[10];
	char localIP[16];
	struct contato contatos[8];
	struct grupo grupos[8];	
}user;
