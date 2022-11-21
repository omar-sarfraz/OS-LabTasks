#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct process{
	int arrivalTime;
	int burstTime;
	int completionTime;
	int turnaroundTime;
	int waitingTime;
};

int main(){

	printf("Enter No. of processes: ");
	int totalProcess;
	scanf("%d", &totalProcess);

	struct process p[totalProcess];

	for(int i=0; i<totalProcess; i++){
		printf("Enter Arrival Time  Process No. %d: ", i+1);
		scanf("%d", &p[i].arrivalTime);

		printf("Enter Burst Time of Process No. %d: ", i+1);
		scanf("%d", &p[i].burstTime);
		p[i].completionTime = 0;
		p[i].turnaroundTime = 0;
		p[i].waitingTime = 0;
	}

	for(int i=0; i<totalProcess; i++){
		int temp = 0, temp2;
		for(int j=i+1; j<totalProcess; j++){
			if(p[i].arrivalTime > p[j].arrivalTime){
				temp = p[i].arrivalTime;
				temp2 = p[i].burstTime;

				p[i].arrivalTime = p[j].arrivalTime;
				p[i].burstTime = p[j].burstTime;

				p[j].arrivalTime = temp;
				p[j].burstTime = temp2;
			}
		}
	}

	int totalBursts = 0;

	for(int i=0; i<totalProcess; i++){
		totalBursts += p[i].burstTime;
		p[i].completionTime = totalBursts;

		p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
		p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
	}

	printf("Order Burst Time ArrivalTime  Waiting Time TurnaroundTime\n");
	for(int i=0; i<totalProcess; i++){
		printf("%d\t %d\t\t %d\t %d\t\t %d\t\n", i+1, p[i].burstTime, p[i].arrivalTime, p[i].waitingTime, p[i].turnaroundTime);
	}
	return 0;
}
