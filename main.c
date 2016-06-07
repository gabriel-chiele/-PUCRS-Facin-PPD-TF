#include <stdio.h>

#include "user.h"
#include "utils.h"
#include "client.h"
#include "server.h"

#define DEBUG

struct user usuario;
FILE* user_file;
char login[9];
char user_fileName[16];
int errn = 0;
pthread_t id;
char aux[5];

int main(void){

	printf("\t\t\tWhatsPPD\nUsuario:");
	fgets(login,sizeof(login),stdin);
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
		//gets(aux);
		if(aux[0] == '.')
			break;
		readSTDIN();
		aux[0] = '.';
/*
		_createTxtMessage(&msg, usuario.userName,"msg em si")
		allocInfo(&info,"ip para onde mandar", msg);
		initClientThread(info);
*/
	}

	#ifndef DEBUG
		atexit(close);
	#endif
}
