#ifndef MENSAGEM_HEADER
#define MENSAGEM_HEADER

#include <stdio.h>
#include "contato.h"

#define TAM_MAX_MSG 33

/** STATUS DA MSG **/
#define CRIADA 0
#define ENVIADA 1
#define LIDA 2

/** TIPOS DE MSG **/
#define MSG_TXT 0
#define ADD_CONTATO 1
#define ADD_GRUPO 2

typedef struct mensagem{
	int tipo;
	char msg[TAM_MAX_MSG];
	char from[9];
	int estado;
}mensagem;

void _createTxtMessage(struct mensagem* new, char* from, char* phrase);
void _createAddContatoMessage(struct mensagem* new, char* from);
/*
void _createAddGrupoMessage(struct contato* from, struct contato* to, struct mensagem* new, char* phrase);
*/
#endif
