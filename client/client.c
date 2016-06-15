#include "client.h"

// TODO: adapt this code to became the methods in the respectivly header file

int allocInfo(struct clientInfo *new, char* ip, struct mensagem* ptr){
	strcpy(new->host_ip, ip);
	new->msg = ptr;
}

void initClientThread(struct clientInfo* info){
	extern int errn;
	int send_socket, port = 1024;

	struct sockaddr_in server;
	struct hostent *host, *gethostbyname();

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
		exit(0);
	}

	send(send_socket, info->msg, sizeof(struct mensagem), 0);

	close(send_socket);
	return;
}

void main(void){
	int parada;
	char host_ip[] = "192.168.229.136";
	struct clientInfo info;
	struct mensagem msgtxt;
	struct mensagem msgadd;

	_createTxtMessage(&msgtxt,"x-client","este de msg de txt");
	allocInfo(&info, host_ip, &msgtxt);

	initClientThread(&info);

	scanf("%d",parada);

	_createAddContatoMessage(&msgadd,"x-client");
	allocInfo(&info, host_ip, &msgadd);

	initClientThread(&info);

}
