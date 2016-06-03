#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <pthread.h>

void readSTDIN(void);
void close(void);
void exitWithERROR(void);
int searchUser(char* username);

#endif

