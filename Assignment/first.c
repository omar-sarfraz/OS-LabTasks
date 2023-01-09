#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int arr[10] = {2,3,4,5,6,7,8,3,2,5};
int found = 0;
int foundAt;
int find = 7;
int initial = 0;

pthread_mutex_t lock;

void *fun(){
	pthread_mutex_lock(&lock);


	if(!found){
		for(int i=initial; i<initial+2; i++){
			if(find == arr[i]){
				found = 1;
				foundAt = i;
			}
		}
		initial+=2;
	}

	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&lock, NULL);

	for(int i=0; i<5; i++){
		pthread_t id;
		pthread_create(&id, NULL, fun, NULL);
		pthread_join(id, NULL);
	}

	pthread_mutex_destroy(&lock);
	printf("%d found at %d\n", find, foundAt);
	
	return 0;
}
