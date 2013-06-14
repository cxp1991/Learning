#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr

#define BUFFER_SIZE 100

int main(int argc , char *argv[])
{
    char message[BUFFER_SIZE] , server_reply[BUFFER_SIZE];
    char *temp = NULL;
	int socket_desc;
	struct sockaddr_in server;
	
	memset(message,'\0',sizeof(message));
	memset(server_reply,'\0',sizeof(server_reply));

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (-1 == socket_desc)
    {
        fprintf(stderr,"Could not create socket!\n");
		return -1;
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (-1 == connect(socket_desc , (struct sockaddr *)&server , sizeof(server)))
    {
        fprintf(stderr,"Connect failed\n");
        return -1;
    }
    puts("Connected");
     
    //Send some data
    temp = "Hello server, I'm client!";
    strncpy(message,temp,strlen(temp));
    if(-1 == write(socket_desc , message , sizeof(message)))
    {
        fprintf(stderr,"Send failed!");
        return -1;
    }
    puts("Data Send");
     
    //Receive a reply from the server
    if(-1 == recv(socket_desc, server_reply , sizeof(server_reply) , 0))
    {
        fprintf(stderr,"Receive failed!");
		return -1;
    }
    puts(server_reply);
    close(socket_desc);
     
    return 0;
}
