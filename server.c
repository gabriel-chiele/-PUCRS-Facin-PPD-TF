#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "server.h"
#include "mensagem.h"

void initThread(void){
	int err;
	pthread_t id;
	err = pthread_create(&id, NULL, &serverThread, NULL);
	printf("iniciei a thread\n");
}

void* handleMsg(int send_socket){
	struct mensagem msg;
	int bytes_received;
	do{
		bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
		printf("%s sent: %s\n", msg.from, msg.msg);
	}while (msg.msg[0] != '.'); 

	close(send_socket);
	return(0);
}

void* serverThread(void){  
	printf("dentro da thread 1\n");     
	int main_socket, err, id; 
	int send_socket, port = 1024;                                         
	struct sockaddr_in server; 
	struct sockaddr client;
	socklen_t socket_length = sizeof(struct sockaddr);                               
	       
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket < 0){                                            
		fprintf(stderr,"Erro ao abrir stream socket");                 
		return(1);                                           
	} 

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;                         
	server.sin_port = htons(port); 
	if (bind(main_socket, (struct sockaddr *)&server, sizeof server ) < 0){
		fprintf(stderr,"Binding stream socket");                 
		return(1);
	}
	   
	listen(main_socket, 5);
	while (1) {
		send_socket = accept(main_socket, &client, &socket_length);
		printf("Talking to %d.%d.%d.%d \n",client.sa_data[2]&0x000000ff, client.sa_data[3]&0x000000ff, client.sa_data[4]&0x000000ff, client.sa_data[5]&0x000000ff); 
		err = pthread_create(&id, NULL, &handleMsg, send_socket);  
	}

	close(main_socket);
	return(0);
} 
