#include "utils.h"

void readSTDIN(void){
	char string[1024];
	char *aux, comando, hash; 
	int i, j, count = 0;

	fgets(string, sizeof(string), stdin);
	hash = string[0];
	if(hash == '#'){
		comando = tolower(string[1]);
		switch(comando){
			case 'i': // add contato com nome e ip dado
				printf("Funciona\n");
				break;
			case 'g': // add grupo com os nomes dados
				printf("Funciona\n");
				break;
			case 'l': // lista as msg do contato com o nome dado
				printf("Funciona\n");
				break;
			case 's': // envia msg para o contato com o nome dado
				printf("Funciona\n");
				break;
			case 'c': // lista todos os contatos e grupos do usuario
				printf("Funciona\n");
				break;
			default: 
				printf("N funciona\n");
				break;
		}
		/*for(i=0;i<strlen(string);i++){
			if(string[i] == ' ' || string[i] == NULL){
				aux = (char*)calloc((i - count),sizeof(char));
				for(j=count;j<i;j++) 
					aux[j] = string[i];
				printf("%d - %s\n", count ,aux);
				count = i;
				printf("%d\n",count);
			}
		}*/
	}
	else printf("\t\t    Comando Invalido\n");
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
			if(!strcmp(dir->d_name,username))
				return 1;
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

