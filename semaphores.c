#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t lock;

void *fun(){
	sem_wait(&lock);
	printf("Start\n");
	sleep(4);
	printf("Finish\n");
	sem_post(&lock);
	pthread_exit(NULL);
}

int main(){
	sem_init(&lock, 0, 1); //2nd Argument 0 for thread, Non-zero for processes. 3rd Argument is initial value;

	pthread_t id, id1;
	
	pthread_create(&id,NULL,fun,NULL);
	sleep(2);
	pthread_create(&id1,NULL,fun,NULL);

	pthread_join(id,NULL);
	pthread_join(id1,NULL);

	sem_destroy(&lock);
	return 0;
}
