#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

	pid_t pid;
	int sum = 0;

	int fds[2];
	int status = pipe(fds);

	if(status == -1){
		printf("Pipe creation failed!\n");
		return 0;
	}

	for(int i=0; i<atoi(argv[1]); i++){
		pid = fork();
		if(pid == -1){
			printf("Process Creation failed!\n");
		} else if(pid == 0){
			printf("\nChild process with id %d started with parent id %d", getpid(), getppid());

			int input = 0;

			printf("\nEnter an integer: ");
			scanf("%d", &input);

			write(fds[1], &input, sizeof(input));
			exit(0);
		} else {
			int output = 0;

			read(fds[0], &output, sizeof(output));

			sum += output;
			wait(NULL);
		}
	}

	printf("\nTotal Sum is %d\n", sum);

}
