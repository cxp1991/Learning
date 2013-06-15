#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define BUFFER_SIZE 100

int main(int argc , char *argv[])
{
    char recbuf[BUFFER_SIZE], sendbuf[BUFFER_SIZE];
    char *temp = NULL;
    int socket_desc , new_socket;
    struct sockaddr_in server , client;
    socklen_t sock_size;
    
    memset(recbuf,'\0',sizeof(recbuf));
    memset(sendbuf,'\0',sizeof(sendbuf));

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (-1 == socket_desc)
    {
        fprintf(stderr,"Could not create socket!\n");
	return -1;
    }
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
     
    //Bind
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        fprintf(stderr,"Bind failed!\n");
        return -1;
    }

    puts("Bind done!");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    sock_size = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, &sock_size);
    if (new_socket < 0)
    {
        fprintf(stderr,"Accept failed!\n");
        return -1;
    }
    
    //Receive client's message
    if(-1 == read(new_socket, recbuf , sizeof(recbuf)))
    {
	fprintf(stderr,"Receive failed!\n");
	return -1;
    }
    puts(recbuf);
     
    //Reply to the client
    temp = "Hello Client , I have received your connection. But I have to go now, bye";
    strncpy(sendbuf, temp, strlen(temp));
    if(-1 == send(new_socket , sendbuf, sizeof(sendbuf), 0))
    {
        fprintf(stderr,"Send failed!\n");
	return -1;
    }
    puts("Sended!");
    
    close(socket_desc);
    close(new_socket);
     
    return 0;
}
