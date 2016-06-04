#include <stdio.h>

#include "user.h"
#include "utils.h"
#include "server.h"

#define DEBUG

struct user usuario;
FILE* user_file;
char login[9];
char user_fileName[16];
int errn = 0;
pthread_t id;

int main(void){

	printf("\t\t\tWhatsPPD\nUsuario:");
	gets(login);
	sprintf(user_fileName,"Users/%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);	
		}
		#ifdef DEBUG
		else{
			DEBUG_printUser(&usuario);
		}
		#endif
	}
	else{
		_createUser(&usuario,login);
		//AddContact(&usuario, "gabriel", "127.0.0.1");
		#ifdef DEBUG
			DEBUG_printUser(&usuario);
		#endif
		if(!saveUser(&usuario, user_fileName)){
			errn = 2;
			atexit(exitWithERROR);
		}
	}

	initServerThread(&id);
	while(1){
		// TODO: add the command parser here along with client thread
		char aux[5];
		gets(aux);
		if(aux[0] == '.')
			break;
	}

	atexit(close);
}
