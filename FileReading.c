#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		printf("Process creation failed!\n");
	}
	else if (pid == 0)
	{
		printf("Child Process started\n");

		// printf("%s\n", argv[1]); --> Print FileName passed as command line argument
		FILE *fptr;
		char ch;
		int newLine = 0, character = 0, blank = 0;
		fptr = fopen(argv[1], "r");
		do
		{
			ch = fgetc(fptr);
			// printf("%c", ch);
			character++;
			if (ch == ' ')
			{
				blank++;
			}
			if (ch == '\n')
			{
				newLine++;
			}
		} while (ch != EOF);

		fclose(fptr);

		printf("New Line characters: %d\n", newLine);
		printf("Blank Characters: %d\n", blank);
		printf("Total  characters: %d\n", character);
		printf("CHild Process ended\n");
		exit(1);
	}
	else
	{
		printf("Parent Process started\n");
		wait(NULL);
		printf("Parent Process ended\n");
	}

	return 0;
}
