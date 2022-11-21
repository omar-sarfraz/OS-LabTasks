#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<error.h>

int main(int argc, char *argv[]){
	pid_t pid;

	for(int i=0; i<2; i++){
		pid=fork();		
		
		if(i==0){
			if(pid == -1){
				printf("Process creation failed!\n");
			} else if(pid == 0){
				//Child
				execl("/bin/touch", "touch", "testFile.txt", NULL);
				perror("touch failed\n");				
				exit(1);
			} else {wait(NULL);}
		}

		if(i==1){
			if(pid == -1){
				printf("Process creation failed!\n");
			} else if(pid == 0){
				//Child
				execl("/bin/cat", "cat", "hello.txt", NULL);
				perror("cat failed\n");
				exit(1);
			} else {
				//Parent
				execl("/bin/rmdir", "rmdir", "test", NULL);
				perror("rmdir failed\n");
				wait(NULL);
			}
		}
		

	}
	return 0;
}
