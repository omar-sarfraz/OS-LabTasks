#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	char* file1 = argv[1];
	char* file2 = argv[2];

	int file1dis = open(file1, O_RDONLY, 0777);
	int file2dis = creat(file2, 0777);

	char* buf[2];
	int c;

	do{
		c = read(file1dis, buf, 1);
		write(file2dis, buf, 1);
	}while(c != 0);

	close(file1dis);
	close(file2dis);
	remove(file1);
	return 0;
}
