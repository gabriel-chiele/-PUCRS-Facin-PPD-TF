#include "server.h"

void initServerThread(pthread_t *id){
	int err;
	err = pthread_create(&id, NULL, &serverThread, NULL);
}

// TODO: handleMsg should be altered to handle all kinds of MSGs, sice now it only accepts txt MSGs
void* handleMsg(int send_socket){
	struct mensagem msg;
	int bytes_received;
	do{
		bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
		if(msg.tipo == MSG_TXT)
			printf("%s sent: %s\n", msg.from, msg.msg);
		else if(msg.tipo == ADD_CONTATO)
			printf("Still not being handle!");
			// TODO: create a contact at global user.
	}while (msg.msg[0] != '.'); 

	close(send_socket);
	return(0);
}

void* serverThread(void){     
	int main_socket, err, id; 
	int send_socket, port = 1024;                                         
	struct sockaddr_in server; 
	struct sockaddr client;
	socklen_t socket_length = sizeof(struct sockaddr);                               
	       
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket < 0){                                            
		fprintf(stderr,"Erro ao abrir stream socket\n");                 
		return(1);                                           
	} 

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;                         
	server.sin_port = htons(port); 
	if (bind(main_socket, (struct sockaddr *)&server, sizeof server ) < 0){
		fprintf(stderr,"Binding stream socket\n");                 
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
