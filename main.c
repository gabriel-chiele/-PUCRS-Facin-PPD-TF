#include <stdio.h>

#include "user.h"
#include "utils.h"

#define DEBUG

struct user usuario;
FILE* user_file;
char login[8];
char user_fileName[15];
int errn = 0;

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
	printf("perdeu");
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
	//atexit(close);
}
