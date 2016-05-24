#include <stdio.h>

#include "contato.h"
#include "mensagem.h"
#include "grupo.h"

void main(void){

	struct grupo group;
	struct contato contatos[8];
	

	_createContato(&contatos[0],"carlos","10.10.10.10");

	printf("Contato Criado:\n%s\n%s\n\n",contatos[0]._name, contatos[0]._ip);

	_createGrupo(&group,"teste",&(contatos[0]),1); 

	printf("Grupo: \n%s\n%s\n",group._name, group.contatos[0]._name);

}
