#include <stdio.h>

void  readSTDIN(void){
	char string[1024];
	int i = 0, separator = 0;
	while(1){
		gets(string);
		for(i=0;i<strlen(string);i++){
			if(string[i] == NULL)
				break;
			else if(string[i] == '\ ')
			{
				printf("%s\n", string);
				separator = i;
			}
			else continue;
		}
	}
	// criar parser para identificar comandos
}

void main(void){
	readSTDIN();
}
