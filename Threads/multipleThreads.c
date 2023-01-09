#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

struct data {
	int value;
	char* message;
};

void * print(void *input){
	struct data *newData = (struct data*)input;
	printf("%d\n", newData -> value);
	printf("%s\n", newData -> message);
	pthread_exit(NULL);
}

int main(){
	struct data thread_data[5];

	for(int i=0; i<5; i++){
		thread_data[i].value = i;
		char msg[] = "Hello World";
		thread_data[i].message = msg;

		pthread_t threadId;
		pthread_create(&threadId,NULL,print,(void *)&thread_data[i]);
		pthread_join(threadId, NULL);
	}
	return 0;
}
