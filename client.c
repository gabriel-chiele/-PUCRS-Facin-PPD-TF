#include "client.h"

// TODO: adapt this code to became the methods in the respectivly header file

int main(int argc, char *argv[]){

	int send_socket, port = 1024;
	char host_ip;

	struct sockaddr_in server;
	struct hostent *host, *gethostbyname();

	char aux[32];
	struct mensagem msg;

	strcpy(host_ip,argv[1]);

	if ((send_socket = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		fprintf(stderr,"Error opening stream socket.");
	 return(1);
	}

	host = gethostbyname(host_ip);
	if (host == 0) {
		fprintf(stderr,"%s: unkown host",host_ip);
		return(2);
	}

	strncpy((char *)&server.sin_addr,(char *)host->h_addr, host->h_length);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(send_socket, (struct sockaddr *)&server, sizeof server ) < 0) {
		fprintf(stderr,"Erro connectando stream socket\n");
		exit(1);
	}

	printf("Talk\n") ;

	do {
    	gets(aux);
    	printf("Enviei: %s \n",aux);
		_createTxtMessage(&msg, "client", aux);
		send(send_socket, &msg, sizeof(struct mensagem), 0);
	} while (msg.msg[0] != '.'); 

	close(send_socket);
	exit(0);
}

//192.168.100.202



