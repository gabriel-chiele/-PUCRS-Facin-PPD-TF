#include <stdio.h>
#include <dirent.h> 

#include "user.h"

struct user usuario;
FILE* user_file;
char login[8];
char aux[10];

void close();
int searchUser(char* username);

void main(void){

	printf("\t\t\tWhatsPPD\nUsuario:");
	gets(login);

	// procurar arquivo para 'login' dado, se ñ existir criar usuario
	sprintf(aux,"%s.u",login);
	if(searchUser(aux)){
		printf("Achou mizeravi !");
	}
	else{
		printf("Nao deu nao.");
	}

	//atexit(close);
}

void close(){
	// salvar e fechar arquivo do usuario aqui
	system("clear");
}

int searchUser(char* username){
	DIR *d;
	struct dirent *dir;
	d = opendir("Users");
	if (d){
		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,username))
				return 1;
		}
	closedir(d);
	}
	return 0;
}

