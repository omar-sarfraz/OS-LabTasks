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

	int c = connect(sockServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if(c == -1) {
		printf("Error\n");
	}
	else {
		char message[255];
		int val = read(sockServer,message,255);
		printf("%s\n",message);

		char msg[255] = "Message from Client 1";
		send(sockServer, msg, sizeof(msg), 0);
	}

	return 0;
}
