#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pid;
	pid = fork();
	if(pid == -1) return 0;
	else if (pid == 0){
		printf("Child\n");
		char *name[] = {"Omar", NULL};
		execv("./task", name);
		exit(1);
	} else {
		printf("Parent\n");
		//Parent does nothing
		wait(NULL);
	}
}
