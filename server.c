#include "server.h"

void CtrlC(int dummy){
	printf("CTRLC\n");
	printf("%d\n",close(main_socket));
	exit(0);
}

void initServerThread(pthread_t *id){
	int err;
	err = pthread_create(&id, NULL, &serverThread, NULL);
}

void* serverThread(void){     
	extern struct user usuario;
	char file_name[26];
	char msg_received[TAM_MAX_MSG];
	int err, id; 
	int send_socket, port = 1024;    
	int bytes_received;                                     
	struct sockaddr_in server; 
	struct sockaddr client;
	socklen_t socket_length = sizeof(struct sockaddr);   

	int ret, enable = 1;

	FILE* msgfile;

	struct mensagem msg;   

	signal(SIGINT, CtrlC);                         
	       
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket < 0){                                            
		fprintf(stderr,"Erro ao abrir stream socket\n");                 
		return(1);                                           
	} 
	if (setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    	error("setsockopt(SO_REUSEADDR) failed");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;                         
	server.sin_port = htons(port); 
	// TODO:
	if ( (ret = bind(main_socket, (struct sockaddr *)&server, sizeof server )) < 0){
		fprintf(stderr,"Binding stream socket %d\n", errno);                 
		return(1);
	}
	   
	listen(main_socket, 5);
	while (1) {
		send_socket = accept(main_socket, &client, &socket_length);
		printf("Talking to %d.%d.%d.%d \n",client.sa_data[2]&0x000000ff, client.sa_data[3]&0x000000ff, client.sa_data[4]&0x000000ff, client.sa_data[5]&0x000000ff); 
		bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
		if(msg.tipo == MSG_TXT){
			printf("pelo menos chegou\n");
			//TODO: criando o arquivo mas ñ salva corretamente a msg
			sprintf(file_name,"Messages/%s.msg",msg.from);
			msgfile = fopen(file_name, "ab");
			strcpy(msg_received,msg.msg);
			fwrite(msg_received, sizeof(msg_received), 1, msgfile);
			printf("%s sent: %s\n", msg.from, msg.msg);
			close(msgfile);
		}
		else if(msg.tipo == ADD_CONTATO){
			printf("Still not being handle!\n");
			// TODO: create a contact at global user.  
		}
		close(send_socket);
	}

	close(main_socket);
	return(0);
} 
