#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int fds[2];
	int status = pipe(fds);

	if(status == -1){
		printf("Pipe creation failed!\n");
		return 0;
	}
	printf("Pipe created!\n");

	pid_t pid;
	pid = fork();

	if(pid == -1){
		printf("Child process creation failed!\n");
		return 0;
	} else if(pid == 0){
		printf("Child Process Started!\n");
		char currentFile[20];
		close(fds[1]);
		read(fds[0], currentFile, sizeof(currentFile));

		FILE *fptr;
		char ch;
		int characters = 0, words = 1;

		fptr = fopen(currentFile, "r");

		printf("\nContents of file: ");
		ch = fgetc(fptr);

		while (ch != EOF) {
			characters++;
			printf("%c", ch);
			if(ch == ' ')
				words++;

			ch = fgetc(fptr);
		}

		fclose(fptr);

		printf("Characters: %d\n", characters);
		printf("Words: %d\n", words);
		printf("\nChild process ended!\n");
		exit(0);
	} else {
		printf("Parent Process Started!\n");
		char* fileName = "data.txt";
		close(fds[0]);
		write(fds[1], fileName, sizeof(fileName));
		wait(NULL);
	}

	return 0;
}
