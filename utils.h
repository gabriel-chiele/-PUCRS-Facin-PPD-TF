#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <pthread.h>

#include "user.h"
#include "client.h"
#include "mensagem.h"

void Login(char* user_fileName);
void executeComandInsertion(struct user* usuario, char* string, int nArgs, char* fileName);
void executeComandSend(struct user* usuario, char* string, int nArgs, char* fileName);
void close(void);
void exitWithERROR(void);
int searchUser(char* username);

#endif

