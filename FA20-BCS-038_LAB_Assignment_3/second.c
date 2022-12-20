#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int arr[10];

pthread_mutex_t lock;
int index1 = -1;

void *produce(){
	pthread_mutex_lock(&lock);
	while(index1 == 9){
	
	}
	index1++;
	arr[index1] = index1;
	printf("%d produced\n", index1);

	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

void *consume(){
	pthread_mutex_lock(&lock);

	while(index1 == -1){
	
	}
	printf("%d consumed\n", index1);
	index1--;

	pthread_mutex_unlock(&lock);	
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&lock, NULL);

	for(int i=0; i<6; i++){
		pthread_t id;
		pthread_create(&id, NULL, produce, NULL);
		pthread_join(id, NULL);
	}

	for(int i=0; i<6; i++){
		pthread_t id2;
		pthread_create(&id2, NULL, consume, NULL);
		pthread_join(id2, NULL);
	}

	pthread_mutex_destroy(&lock);
	
	return 0;
}
