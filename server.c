#include "server.h"

void CtrlC(int dummy){
	printf("TRL+C\n");
	printf("%d\n",close(main_socket));
	exit(0);
}

void initServerThread(pthread_t *id){
	int err;
	err = pthread_create(&id, NULL, &serverThread, NULL);
}

void* serverThread(void){     
	extern struct user usuario;
	char file_name[26], msg_received[TAM_MAX_MSG];
	char ip[16];
	int err, id, contact_index; 
	int send_socket, port = 1024;    
	int bytes_received;                                     
	struct sockaddr_in server; 
	struct sockaddr client;
	socklen_t socket_length = sizeof(struct sockaddr);   

	int ret, enable = 1;

	FILE* msgfile;

	struct mensagem msg;   

	signal(SIGINT, CtrlC);  
	clearMSG(msg_received, TAM_MAX_MSG); 
	clearMSG(ip, 16);                      
	       
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket < 0){                                            
		fprintf(stderr,"Erro ao abrir stream socket\n");                 
		return(1);                                           
	} 
	if (setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
		errn = 4;    	
		exit(0);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;                         
	server.sin_port = htons(port); 
	if ( (ret = bind(main_socket, (struct sockaddr *)&server, sizeof server )) < 0){
		fprintf(stderr,"Binding stream socket %d\n", errno);                 
		return(1);
	}
	   
	listen(main_socket, 5);
	while (1) {
		send_socket = accept(main_socket, &client, &socket_length); 
		sprintf(ip, "%d.%d.%d.%d\0",client.sa_data[2]&0x000000ff, client.sa_data[3]&0x000000ff, client.sa_data[4]&0x000000ff, client.sa_data[5]&0x000000ff);
		bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
		pthread_mutex_lock(&lock);
		if(msg.tipo == MSG_TXT){	//TODO: depois de salvar a msg enviar confirmação de recebimento para que o cliente que gerou a msg tbm n possa salvar no seu arquivo.
			if( ContactwithNameExist(&usuario, msg.from) >= 0){
				sprintf(file_name,"Messages/%s.msg",msg.from);
				msgfile = fopen(file_name, "ab");
				strcpy(msg_received,msg.msg);
				fwrite(msg_received, sizeof(msg_received), 1, msgfile);
				fflush(msgfile);
				close(msgfile);
				clearMSG(msg_received, TAM_MAX_MSG); 
			}
		}
		else if(msg.tipo == ADD_CONTATO){	//TODO: depois de verificar a possibilidade de add enviar msg de volta para confirmar ou negar a add, se negar o cliente que gerou a msg tbm n pode add
			if( ContactwithNameExist(&usuario, msg.from) < 0){
				if((contact_index = usuario.nContatos) < 8){
					printf("Contato novo\n");
	 				AddContact(&usuario, msg.from, ip);
					printf("%s\n",&usuario.file_name);
					saveUser(&usuario, usuario.file_name);
				}
				else printf("Total de contatos ja atingido\n");
			}
			else printf("Contato com este nome ou ip ja existe em sua lista de de contatos\n");
		}
		pthread_mutex_unlock(&lock);
		close(send_socket);
	}

	close(main_socket);
	return(0);
} 
