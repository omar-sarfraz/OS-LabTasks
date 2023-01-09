#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/*struct data {
	int value;
	char* message;
};*/

int series[8];

void * print(void *input){

	int * data = (int *)input;
	int data2 = *data;	
	if(data2 == 0){
		series[0] = data2;	
	} else if (data2 == 1){
		series[1] = data2;	
	} else {
		series[data2] = series[data2-1] + series[data2-2];
	}
	pthread_exit(NULL);
}

int main(){
	//struct data thread_data[5];

	for(int i=0; i<8; i++){
		pthread_t threadId;
		pthread_create(&threadId,NULL,print,(void *)&i);
		pthread_join(threadId, NULL);
	}

	for(int i=0; i<8; i++){
		printf("%d ",series[i]);
	}
	return 0;
}
