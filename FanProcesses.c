// Create n number of fan processes where child communicates with parent by sending a string & parent prints them on console. n is command line argument.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fds[2];
	int status = pipe(fds);

	if (status == -1)
	{
		printf("Failed to create a pipe\n");
		return 0;
	}
	printf("Pipe created!\n");

	char input[15];
	char output[15];

	pid_t pid;

	for (int i = 0; i < atoi(argv[1]); i++)
	{
		pid = fork();

		if (pid == -1)
		{
			printf("Failed to create a process!\n");
		}
		else if (pid == 0)
		{
			printf("Child Process with id: %d!\n", getpid());
			printf("Enter a string: ");
			gets(input);
			write(fds[1], input, sizeof(input));
			printf("Child Process end!\n");
			exit(1);
		}
		else
		{
			printf("Parent Process id: %d\n", getpid());
			read(fds[0], output, sizeof(output));
			printf("Output: %s\n", output);
			wait(NULL);
		}
	}
	return 0;
}
