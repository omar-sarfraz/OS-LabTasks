#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

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

		char *fmsg = "Asma";
		char data[50];
		char *tmsg = "MSCS";

		write(fd1[1], fmsg, sizeof(fmsg));
		read(fd2[0], data, sizeof(data));
		strcat(data, " ");
		strcat(data, tmsg);
		write(fd1[1], data, sizeof(data));

		exit(1);
	} else {
		//PArent
		close(fd2[0]); // Closed read for fd2
		close(fd1[1]); // Closed write for fd1

		char *smsg = "FA20-RCS-022";
		char data[50];

		read(fd1[0], data, sizeof(data));
		strcat(data, " ");
		strcat(data, smsg);
		write(fd2[1], data, sizeof(data));

		read(fd1[0], data, sizeof(data));

		printf("Parent output: %s\n",data);
		wait(NULL);
	}

	return 0;
}
