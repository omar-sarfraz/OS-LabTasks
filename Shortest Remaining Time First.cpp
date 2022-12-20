#include<iostream>
#include<windows.h>

using namespace std;

struct process {
    int arrivalTime = 0;
    int burstTime = 0;
    int completedBursts = 0;
    int completionTime = 0;
    int remainingBursts = 0;
};

int minimumArrivalTimeIndex(process p[], int totalProcesses){
    int minimumIndex = 0, minimum = p[0].arrivalTime;

    int decide = 0;
    while(p[decide].completionTime > 0){
        decide++;
    }

    minimumIndex = decide;
    minimum = p[decide].arrivalTime;

    for(int i=decide+1; i<totalProcesses; i++){
        if( p[i].completionTime > 0 ){
            continue;
        }
        if(p[i].arrivalTime < minimum){
            minimum = p[i].arrivalTime;
            minimumIndex = i;
        }
    }
    return minimumIndex;
}

int duplicateMinimumArrival(process p[], int totalProcesses, int minimumArrivalIndex){
    int shortBurstIndex = minimumArrivalIndex;

    for(int i=0; i<totalProcesses; i++){
        if( p[i].completionTime > 0 ){
            continue;
        }
        if( p[minimumArrivalIndex].arrivalTime == p[i].arrivalTime ){
                if( p[i].burstTime < p[minimumArrivalIndex].burstTime ){
                        if( p[i].completionTime == 0 ){
                            shortBurstIndex = i;
                        }
                }
        }
    }
    return shortBurstIndex;
}

int checkNewProcessArrival(int currentBurst, int currentProcessIndex, process p[], int totalProcesses){
    int runThisProcess = currentProcessIndex;

    //cout << "Current: " << currentProcessIndex << endl;

    for(int i=0; i<totalProcesses; i++){
        if( p[i].arrivalTime <= currentBurst && p[i].remainingBursts !=0 ){
            if( p[i].remainingBursts < p[runThisProcess].remainingBursts ){
                //cout << "Remaining Next: " << p[i].remainingBursts << " Remaining Current: " << p[currentProcessIndex].remainingBursts << endl;
                runThisProcess = i;
            }
        }
    }

    //cout << "Returened: " << runThisProcess << endl;
    return runThisProcess;
}

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

int main(){
    int totalProcesses;

    inputProcesses:
    cout << "Enter the number of processes: ";
    cin >> totalProcesses;

    if(cin.fail() || totalProcesses <= 0){
            cout << "Wrong Input! Number of processes must be an integer greater than 0!" << endl;
            cin.clear();
            cin.ignore(2000, '\n');
            goto inputProcesses;
    }

    process p[totalProcesses];

    for(int i=0; i<totalProcesses; i++){
        inputArrivalTime:
        cout << "Enter arrival time of process number " << i+1 << ": ";
        cin >> p[i].arrivalTime;

        if(cin.fail() || p[i].arrivalTime < 0){
            cout << "Wrong Input! Arrival time must be a positive number!" << endl;
            cin.clear();
            cin.ignore(2000, '\n');
            goto inputArrivalTime;
        }

        inputBurstTime:
        cout << "Enter burst time of process number " << i+1 << ": ";
        cin >> p[i].burstTime;

        if(cin.fail() || p[i].burstTime <= 0){
            cout << "Wrong Input! Burst time must be an integer greater than 0!" << endl;
            cin.clear();
            cin.ignore(2000, '\n');
            goto inputBurstTime;
        }

        p[i].remainingBursts = p[i].burstTime;
    }

    int runThis = minimumArrivalTimeIndex(p, totalProcesses);
    runThis = duplicateMinimumArrival(p, totalProcesses, runThis);
    int completedProcess = 0;
    int totalBursts = p[runThis].arrivalTime;

    //cout << "Run this: " << runThis << endl;
    gotoxy(0, totalProcesses*3);
    for(int i=0; i<100; i++){
        cout << "-";
    }
    cout << endl;

    gotoxy(0, (totalProcesses*3) + 2);
    for(int i=0; i<100; i++){
        cout << "-";
    }
    cout << endl;

    int x=0;
    int prevIndex = runThis;

    gotoxy(x, (totalProcesses*3)+1);

    cout << minimumArrivalTimeIndex(p, totalProcesses) << "     ";

    while(completedProcess != totalProcesses){
        //cout << "Remaining bursts before of " << runThis+1 << ": " << p[runThis].remainingBursts << endl;

        p[runThis].completedBursts++;
        p[runThis].remainingBursts--;
        totalBursts++;

        if(p[runThis].completedBursts == p[runThis].burstTime){
            completedProcess++;
            p[runThis].completionTime = totalBursts;
        }
        //cout << "Complete: " << completedProcess << " Index: " << runThis << endl;
        //cout << "Remaining bursts of " << runThis+1 << ": " << p[runThis].remainingBursts << endl;

        runThis = minimumArrivalTimeIndex(p, totalProcesses);
        runThis = duplicateMinimumArrival(p, totalProcesses, runThis);

        //break;
        //Check if new process is arrived at current burst time whose burstTime is less than current running process
        //cout << endl;
        //cout << "Process No. before new arrival: " << runThis+1 << endl;
        runThis = checkNewProcessArrival(totalBursts, runThis, p, totalProcesses);
        //cout << "Process No. after new arrival: " << runThis+1 << " Previous: " << prevIndex+1 << endl;

        if(runThis != prevIndex) {
            cout << "P" << prevIndex+1 << "     " << totalBursts <<"|" << totalBursts <<"     ";
        }

        prevIndex = runThis;
    }

    cout << endl;
    cout << endl;
    for(int i=0; i<totalProcesses; i++){
        cout << endl;
        cout << "Arrival Time " << i+1 << ": " << p[i].arrivalTime << endl;
        cout << "Burst Time " << i+1 << ": " << p[i].burstTime << endl;
        cout << "Completion Time " << i+1 << ": " << p[i].completionTime << endl;
        cout << "Completed Bursts " << i+1 << ": " << p[i].completedBursts << endl;
    }

    float turnaroundTime = 0;
    for(int i=0; i<totalProcesses; i++){
        turnaroundTime += (p[i].completionTime - p[i].arrivalTime);
    }
    turnaroundTime /= totalProcesses;
    cout << endl;
    cout << "Average Turnaround time: " << turnaroundTime << endl;

    float waitingTime = 0;
    for (int i=0; i<totalProcesses; i++){
        waitingTime += (( p[i].completionTime - p[i].arrivalTime ) - p[i].burstTime);
    }
    waitingTime /= totalProcesses;

    cout << endl;
    cout << "Average Waiting time: " << waitingTime << endl;

    return 0;
}
