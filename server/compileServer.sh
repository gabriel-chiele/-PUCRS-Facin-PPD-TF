#!/bin/bash

gcc -w serverTest.c ../contato.c ../mensagem.c -o exe -lpthread

./exe

#clear
