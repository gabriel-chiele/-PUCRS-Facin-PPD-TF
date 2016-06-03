#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "mensagem.h"

int main(int argc, char *argv[])
{

  int send_socket;

  struct sockaddr_in server;
  struct hostent *host, *gethostbyname();

  char aux[32];
  struct mensagem msg;

  if (argc < 3) {
     printf(" Numero de parametros insuficientes\n") ;
     printf(" Digite o nome do programa, servidor e o numero da porta\n") ;
     return(1) ;
    }
    
  send_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (send_socket  <0) {
     fprintf(stderr,"Error opening stream socket.");
     return(1);
  }

  host = gethostbyname(argv[1]);
  if (host == 0) {
     fprintf(stderr,"%s: unkown host",argv[1]);
     return(2);
  }
  
  strncpy((char *)&server.sin_addr,(char *)host->h_addr, host->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  
  if (connect(send_socket, (struct sockaddr *)&server, sizeof server ) < 0) {
    fprintf(stderr,"Erro connectando stream socket");
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



