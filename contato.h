#ifndef CONTATO_HEADER
#define CONTATO_HEADER

typedef struct contato{
	char* _name;
	char* _ip;
	char* file_name;
	FILE* msgs;
}contato;

int _createContato(struct contato* new, char* name, char* ip);

#endif
