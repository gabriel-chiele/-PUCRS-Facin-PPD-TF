#include "utils.h"

void Login(char* user_fileName){
	extern int errn;
	extern struct user usuario;
	char login[9];

	printf("\t\t\tWhatsPPD\nUsuario:");
	fgets(login,sizeof(login),stdin);
	login[strlen(login)-1] = '\0'; // ADD NULL CHARACTER AT THE END OF USER NAME
	sprintf(user_fileName,"%s.u",login);
	if(searchUser(user_fileName)){
		if(!loadUser(&usuario, user_fileName)){
			errn = 1;
			atexit(exitWithERROR);
			return;	
		}
		sprintf(user_fileName,"Users/%s.u",login);
		#ifdef DEBUG
			printf("DEBUG\n");
			DEBUG_printUser(&usuario);
		#endif
	}
	else{
		sprintf(user_fileName,"Users/%s.u",login);
		_createUser(&usuario,login);
		#ifdef ADD_CONTACT
			AddContact(&usuario, "gabriel", "127.0.0.1");
		#endif
		#ifdef DEBUG
			DEBUG_printUser(&usuario);
		#endif
		if(!saveUser(&usuario, user_fileName)){
			errn = 2;
			atexit(exitWithERROR);
		}
	}
}

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

