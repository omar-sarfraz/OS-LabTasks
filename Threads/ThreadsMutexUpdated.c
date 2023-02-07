#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int counter;

pthread_mutex_t lock;

void * print(void *input){

	pthread_mutex_lock(&lock);
	counter++;
	printf("%d started\n", counter);
	sleep(2);
	printf("%d finish\n", counter);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&lock, NULL);
	pthread_t id1, id2;
	pthread_create(&id1,NULL,print,NULL);
	pthread_join(id1, NULL);

	pthread_create(&id2,NULL,print,NULL);
	pthread_join(id2, NULL);

	pthread_mutex_destroy(&lock);
	return 0;
}
