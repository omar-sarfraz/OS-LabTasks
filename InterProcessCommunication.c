#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int fds[2];
	int status = pipe(fds);

	if(status == -1){
		printf("Failed to create a pipe\n");
		return 0;
	}
	printf("Pipe created!\n");

	char input[15];
	char output[15];

	pid_t pid;

	pid = fork();

	if(pid == -1){
		printf("Failed to create a process!\n");
	}
	else if(pid == 0){
		printf("Child Process started!\n");
		printf("Enter a string: ");
		gets(input);
		write(fds[1], input, sizeof(input));
		printf("Child Process end!\n");
	} else {
		printf("Parent Process started!\n");
		read(fds[0], output, sizeof(output));
		printf("%s\n", output);
		wait(NULL);
		printf("Parent Process end!\n");
	}
	return 0;
}
