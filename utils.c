#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

#include "utils.h"

void  readSTDIN(void){
	char string[1024];
	char *aux, comando; 
	int i, j, count = 0;
	while(1){
		gets(string);
		/* TODO:
		sscanf(string,"%s",comando);
		switch(comando){
			// if the 'comando' is a commad with static number of arguments then utilize sscanf
			// else if the command has variable size, then count the number of spaces to know his size
			// then treat properly
		}
		*/
		for(i=0;i<strlen(string);i++){
			if(string[i] == ' ' || string[i] == NULL){
				aux = (char*)calloc((i - count),sizeof(char));
				for(j=count;j<i;j++) 
					aux[j] = string[i];
				printf("%d - %s\n", count ,aux);
				count = i;
				printf("%d\n",count);
			}
		}
	}
}

void close(void){
	//TODO: Close client and server thread here, along with any possibly open file.
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

void exitWithERROR(void){
	extern errn;
	printf("\t\tProgram terminated\n\t\t     ERROR n:%d\n",errn);
	switch(errn){
		case 1:
			printf("\tUser file exist, but couldn't be opened.\n");
			break;
		case 2:
			printf("\tUser file couldn't be created for some reason.\n");
			break;
		default:
			printf("\tUndefined error occurred.\n\tPlease, contact developers.");
			break;
	}
}

