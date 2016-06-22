#include "client.h"

/** Criação de estrutura auxiliar utilizada pelo client **/
int allocInfo(struct clientInfo *new, char* ip, struct mensagem* ptr){
	strcpy(new->host_ip, ip);
	new->msg = ptr;
}

/** Inicialização de um client **/
int initClient(struct clientInfo* info){
	extern int errn;
	int send_socket, bytes_received, port = 1024;
	int ret;

	struct sockaddr_in server;
	struct hostent *host, *gethostbyname();

	struct mensagem ret_msg;

	/** Criação do socket de transmissão **/
	if ((send_socket = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		fprintf(stderr,"Error opening stream socket.");
		return;
	}

	/** Localização do Host **/
	host = gethostbyname(info->host_ip);
	if (host == 0) {
		fprintf(stderr,"%s: unkown host",info->host_ip);
		return;
	}

	strncpy((char *)&server.sin_addr,(char *)host->h_addr, host->h_length);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	/** Conexão com o Host **/
	if ((ret = connect(send_socket, (struct sockaddr *)&server, sizeof server )) < 0) {
		//TODO: não dar msg erro, ao invés disso, se conexão ñ for realizada,\
				salvar msg em pendentes e retornar do método com retorno 2
		errn = 3;
		exitWithERROR();
	}

	/** Envio da Mensagem **/
	send(send_socket, info->msg, sizeof(struct mensagem), 0);

	/** Espera por confirmação de recebimento **/
	while(1){
		bytes_received = recv(send_socket, &ret_msg, sizeof(struct mensagem), 0);
		close(send_socket);
		if(ret_msg.tipo == RET_MSG_OK){
			return 1;
		}
		else if(ret_msg.tipo == RET_MSG_FAIL){
			printf("\n%s\n",ret_msg.msg);
			return 0;
		}
		else{
			printf("Received wrong type of message!\n");
			continue;
		}
	}
}
