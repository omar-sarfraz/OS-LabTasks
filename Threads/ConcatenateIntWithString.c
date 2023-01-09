#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

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
		char buf[15];
		sprintf(buf, "Hello World %d", i);

		thread_data[i].message = buf;

		pthread_t threadId;
		pthread_create(&threadId,NULL,print,(void *)&thread_data[i]);
		pthread_join(threadId, NULL);
	}
	return 0;
}
