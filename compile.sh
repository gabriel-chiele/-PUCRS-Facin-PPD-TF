#!/bin/bash

gcc -w -Wno-deprecated main.c contato.c mensagem.c grupo.c user.c utils.c server.c client.c -o main -lpthread

#clear
