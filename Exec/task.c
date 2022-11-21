#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int sum = 0;
	for(int i=1; i<argc; i++){
		sum = sum + atoi(argv[i]);
	}
	printf("Sum is: %d\n", sum);
}
