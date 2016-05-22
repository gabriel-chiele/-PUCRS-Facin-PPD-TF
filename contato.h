#ifndef CONTATO_HEADER
#define CONTATO_HEADER

#define N_ELEMENTS(c)  (sizeof(c) / sizeof((c)[0]))

typedef struct contato{
	char _name[8];
	char _ip[16];
	char file_name[25];
}contato;

struct contato _createContato(char* name, char* ip);

void _listMsgs(struct contato* contact_list, char* name);

#endif
