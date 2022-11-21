#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc, char* argv[]){
	pid_t pid;

	pid = fork();

	if(pid == -1){
		printf("Fork failed!\n");
	} else if(pid == 0){
		//Child
		execl("/bin/touch","touch", argv[1], NULL);
		exit(1);
	} else {
		//Parent
		execl("/bin/mkdir","mkdir", argv[2], NULL);
		wait(NULL);
	}

	return 0;
}
