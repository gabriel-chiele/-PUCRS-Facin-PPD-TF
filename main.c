#include <stdio.h>

#include "user.h"
#include "utils.h"

struct user usuario;
FILE* user_file;
char login[15];
char user_fileName[15];
int errn = 0;

int main(void){

	printf("\t\t\tWhatsPPD\nUsuario:");

	gets(login);
	// procurar arquivo para 'login' dado, se ñ existir criar usuario
	sprintf(user_fileName,"%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);	
		}
	}
	else{
		printf("Errro !\n");
	}

	//atexit(close);
}

