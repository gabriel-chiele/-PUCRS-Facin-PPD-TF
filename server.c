#include "server.h"

/** Callback para interceptação de sinais ^C **/
void CtrlC(int dummy){
	printf("TRL+C\n");
	printf("Close main_socket return value: %d\n",close(main_socket));
	printf("Close send_socket return value: %d\n",close(send_socket));
	exit(0);
}

/** Método de inicialização da Thread do servidor **/
void initServerThread(pthread_t *id){
	int err;
	err = pthread_create(&id, NULL, &serverThread, NULL);
}

/** Execução do servidor **/
void* serverThread(void){     
	extern struct user usuario;
	char file_name[26], msg_received[TAM_MAX_MSG];
	char ip[16];
	int err, id, contact_index; 
	int port = 1024;    
	int bytes_received;                                     
	struct sockaddr_in server; 
	struct sockaddr client;
	socklen_t socket_length = sizeof(struct sockaddr);   

	int ret, enable = 1;

	FILE* msgfile;

	struct mensagem msg, ret_msg;   

	/** Atribuição do Callback para sinais de ^C **/
	signal(SIGINT, CtrlC);  

	/** Limpeza das strings **/
	memset(msg_received, '\0', TAM_MAX_MSG);
	memset(ip, '\0', 16);                     
	       
	/** Criação do Socket principal do servidor **/
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket < 0){                                            
		fprintf(stderr,"Erro ao abrir stream socket\n");                 
		return(1);                                           
	} 

	/** Definindo configurações do socket principal **/
	if (setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
		errn = 4;    	
		exit(0);
	}

	/** Atribuindo endereço de IP ao servidor **/
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;                         
	server.sin_port = htons(port); 
	if ( (ret = bind(main_socket, (struct sockaddr *)&server, sizeof server )) < 0){
		fprintf(stderr,"Binding stream socket %d\n", errno);                 
		return(1);
	}
	   
	/** Esperando requisições de conexão **/
	listen(main_socket, 5);
	while (1) {
		/** Aceitando uma conexão e criando socket de comunicação **/
		send_socket = accept(main_socket, &client, &socket_length);
		if(send_socket == -1) {
			break;	
		}
		sprintf(ip, "%d.%d.%d.%d\0",client.sa_data[2]&0x000000ff,\
								    client.sa_data[3]&0x000000ff,\
									client.sa_data[4]&0x000000ff,\
									client.sa_data[5]&0x000000ff);
		/** Recebendo pacote **/
		bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
		pthread_mutex_lock(&lock);
		/** Tratando mensagens de texto recebidas **/
		if(msg.tipo == MSG_TXT){
			/** Se contato com nome e ip não existe na lista de contatos do usuario **/			
			if(ContactExist(&usuario, msg.from, ip) >= 0){
				/** Salva a mensagem **/
				sprintf(file_name,"Messages/%s.msg",msg.from);
				msgfile = fopen(file_name, "ab");
				sprintf(msg_received, "<-- %s",msg.msg);
				fwrite(msg_received, sizeof(msg_received), 1, msgfile);
				fflush(msgfile);
				close(msgfile);
				/** e responde que a operação foi bem sucedida **/
				_createResponseMessage(&ret_msg, usuario.userName, 1, "");
				send(send_socket, &ret_msg, sizeof(struct mensagem), 0);
				memset(msg_received, '\0', TAM_MAX_MSG); 
			}
			/** Senão envia reposta com mensagem de erro **/	
			else{
				printf("Mensagem de contato desconhecido\n");
				_createResponseMessage(&ret_msg, usuario.userName, 0, "Mensagem de contato desconhecido\n");
				send(send_socket, &ret_msg, sizeof(struct mensagem), 0);
			}
		}
		/** Tratando mensagens de inserção de contato **/
		else if(msg.tipo == ADD_CONTATO){
			/** Se contato com nome e ip não existe na lista de contatos do usuario **/	
			if(ContactExist(&usuario, msg.from, ip) < 0){
				/** e há espaço para a adição de mais um contato **/	
				if((contact_index = usuario.nContatos) < 8){
					/** adiciona o contato **/
					printf("Contato novo\n");
	 				AddContact(&usuario, msg.from, ip);
					printf("%s\n",&usuario.file_name);
					saveUser(&usuario, usuario.file_name);
					/** e responde que a operação foi bem sucedida **/
					_createResponseMessage(&ret_msg, usuario.userName, 1, "");
					send(send_socket, &ret_msg, sizeof(struct mensagem), 0);
				}
				/** Senão envia reposta com mensagem de erro **/
				else{
					printf("Total de contatos ja atingido\n");
					_createResponseMessage(&ret_msg, usuario.userName, 0, "Total de contatos ja atingido\n");
					send(send_socket, &ret_msg, sizeof(struct mensagem), 0);
				}
			}
			/** Senão envia reposta com mensagem de erro **/
			else{ 
				printf("Contato com este nome ou ip ja existe em sua lista de de contatos\n");
				_createResponseMessage(&ret_msg, usuario.userName, 0, "Contato com este nome ou ip ja existe em sua lista de de contatos\n");
				send(send_socket, &ret_msg, sizeof(struct mensagem), 0);
			}
		}
		pthread_mutex_unlock(&lock);
		/** Fecha socket de comunicação **/
		close(send_socket);
	}

	/** Fecha socket principal **/
	close(main_socket);
	return(0);
} 
