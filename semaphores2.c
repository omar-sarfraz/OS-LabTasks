#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t lock;
int val = 10;

void *inc(){
	sem_wait(&lock);
	val++;
	sem_post(&lock);
	//printf("%d\n",val);
	pthread_exit(NULL);
}

void *dec(){
	sem_wait(&lock);
	val--;
	sem_post(&lock);
	//printf("%d\n",val);
	pthread_exit(NULL);
}

int main(){
	sem_init(&lock, 0, 1); //2nd Argument 0 for thread, Non-zero for processes. 3rd Argument is initial value;

	for(int i=0; i<4; i++){
		pthread_t id;
		pthread_create(&id,NULL,inc,NULL);
		pthread_join(id,NULL);
	}
	
	for(int i=0; i<6; i++){
		pthread_t id1;
		pthread_create(&id1,NULL,dec,NULL);
		pthread_join(id1,NULL);
	}

	printf("Val: %d\n", val);

	sem_destroy(&lock);
	return 0;
}
