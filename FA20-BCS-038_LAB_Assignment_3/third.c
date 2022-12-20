#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t val;

void *inc(){
	sem_post(&val);
	pthread_exit(NULL);
}

void *dec(){
	sem_wait(&val);
	pthread_exit(NULL);
}

int main(){
	sem_init(&val, 0, 10);
	
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

	int final;
	sem_getvalue(&val, &final);

	printf("Final Value: %d\n", final);

	sem_destroy(&val);
	return 0;
}
