#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

int main(){
	int sockServer = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(2000);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(sockServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	server:
	listen(sockServer, 5);

	int client = accept(sockServer, NULL, NULL);
	char message[255] = "Hello from Server";
	send(client, message, sizeof(message), 0);

	char msg[255];
	read(client, msg, 255);
	printf("Server Prints: %s\n",msg);

    goto server;
	return 0;
}
