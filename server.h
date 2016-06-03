#ifndef SERVER_HEADER
#define SERVER_HEADER 

void initThread(void);
void* handleMsg(int send_socket);
void* serverThread(void);

#endif
