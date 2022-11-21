#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int fd1[2];
	int fd2[2];

	int status1 = pipe(fd1);
	int status2 = pipe(fd2);

	if(status1 == -1 || status2 == -1){
		printf("Failed to create pipe!\n");
		return 0;
	}

	pid_t pid;

	pid = fork();

	if(pid == -1){
		printf("Failed to create child process!\n");
	} else if (pid == 0){
		//Child
		close(fd1[0]); // Closed read for fd1
		close(fd2[1]); // Closed write for fd2

		char *s1 = "Hello";
		char output[20];

		write(fd1[1], s1, sizeof(s1));
		read(fd2[0], output, sizeof(output));

		printf("Child output: %s\n",output);
		exit(1);
	} else {
		//PArent
		close(fd2[0]); // Closed read for fd2
		close(fd1[1]); // Closed write for fd1

		char *s1 = "World";
		char output[20];

		write(fd2[1], s1, sizeof(s1));
		read(fd1[0], output, sizeof(output));

		printf("Parent output: %s\n",output);
		wait(NULL);
	}

	return 0;
}
