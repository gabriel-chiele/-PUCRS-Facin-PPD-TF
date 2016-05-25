#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  readSTDIN(void){
	char string[1024];
	char *aux; 
	int i, j, count = 0;
	while(1){
		gets(string);
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
