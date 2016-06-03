#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "mensagem.h"

int main()
{       
    int main_socket;                                          
    struct sockaddr_in server; 

    struct sockaddr client;
    socklen_t socket_length = sizeof(struct sockaddr);                               
      
    int bytes_received, f, send_socket;                                          
	int port = 1024;
	struct mensagem msg;
                                                               
    /* Create main_socketet. */                  

    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket < 0) {                                            
      fprintf(stderr,"Erro ao abrir stream socket");                 
      return(1);                                           
    } 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;                         
    server.sin_port = htons(port); 
    if (bind(main_socket, (struct sockaddr *)&server, sizeof server ) < 0) {
        fprintf(stderr,"Binding stream socket");                 
        return(1);
    }

    /*Waiting client conection*/ 
       
    listen(main_socket, 5);
    while (1) {
    
      send_socket = accept(main_socket, &client, &socket_length);
   
      printf("Talking to %d.%d.%d.%d \n",client.sa_data[2]&0x000000ff, client.sa_data[3]&0x000000ff, client.sa_data[4]&0x000000ff, client.sa_data[5]&0x000000ff); 

      f = fork();
    
      if (f == 0) {
        do {
        	bytes_received = recv(send_socket, &msg, sizeof(struct mensagem), 0);
	   		printf("%s sent: %s\n", msg.from, msg.msg);
		}while (msg.msg[0] != '.'); 
   
        close(send_socket);
        return(0);
      }  
   
   }
   
   close(main_socket);
   return(0);
   
 } 
