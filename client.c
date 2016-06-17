#include "client.h"

// TODO: adapt this code to became the methods in the respectivly header file

int allocInfo(struct clientInfo *new, char* ip, struct mensagem* ptr){
	strcpy(new->host_ip, ip);
	new->msg = ptr;
}

int initClient(struct clientInfo* info){
	extern int errn;
	int send_socket, bytes_received, port = 1024;

	struct sockaddr_in server;
	struct hostent *host, *gethostbyname();

	struct mensagem ret_msg;

	if ((send_socket = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		fprintf(stderr,"Error opening stream socket.");
		return;
	}

	host = gethostbyname(info->host_ip);
	if (host == 0) {
		fprintf(stderr,"%s: unkown host",info->host_ip);
		return;
	}

	strncpy((char *)&server.sin_addr,(char *)host->h_addr, host->h_length);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(send_socket, (struct sockaddr *)&server, sizeof server ) < 0) {;
		errn = 3;
		exitWithERROR();
	}

	send(send_socket, info->msg, sizeof(struct mensagem), 0);

	while(1){
		bytes_received = recv(send_socket, &ret_msg, sizeof(struct mensagem), 0);
		close(send_socket);
		if(ret_msg.tipo == RET_MSG_OK){
			return 1;
		}
		else if(ret_msg.tipo == RET_MSG_FAIL){
			return 0;
		}
		else{
			printf("Received wrong type of message!\n");
			continue;
		}
	}
}
