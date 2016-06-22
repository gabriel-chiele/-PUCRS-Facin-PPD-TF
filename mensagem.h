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
#define RET_MSG_OK 3
#define RET_MSG_FAIL 4
#define READ_MSGS 5

typedef struct mensagem{
	int tipo;
	char msg[TAM_MAX_MSG];
	char from[9];
	int estado;
}mensagem;

void _createTxtMessage(struct mensagem* new, char* from, char* phrase);
void _createAddContatoMessage(struct mensagem* new, char* from);
void _createResponseMessage(struct mensagem* new, char* from, int status, char* phrase);
void _createListMessage(struct mensagem* new, char* from);
/*
void _createAddGrupoMessage(struct contato* from, struct contato* to, struct mensagem* new, char* phrase);
*/
#endif
