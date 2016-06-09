#include "utils.h"

void close(void){
	//TODO: Close client and server thread here, along with any possibly open file.
	extern pthread_t id;
	pthread_join(id, NULL);
	system("clear");
}

int searchUser(char* username){
	DIR *d;
	struct dirent *dir;
	d = opendir("Users");
	if (d){
		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,username)){
				return 1;
			}
		}
		closedir(d);
	}
	return 0;
}

void exitWithERROR(void){
	extern int errn;
	printf("\t\tProgram terminated\n\t\t     ERROR n:%d\n",errn);
	switch(errn){
		case 1:
			printf("\tUser file exist, but couldn't be opened.\n");
			break;
		case 2:
			printf("\tUser file couldn't be created for some reason.\n");
			break;
		case 3:
			printf("\t?\n");
			break;
		default:
			printf("\tUndefined error occurred.\n\tPlease, contact developers.");
			break;
	}
}

