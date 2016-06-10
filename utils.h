#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <pthread.h>

void Login(char* user_fileName);
void close(void);
void exitWithERROR(void);
int searchUser(char* username);

#endif

