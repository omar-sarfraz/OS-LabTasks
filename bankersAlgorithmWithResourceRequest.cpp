#include<iostream>

using namespace std;

int main(){
    int totalProcess, totalResource;

    processInput:
    cout << "Enter total number of processes: ";
    cin >> totalProcess;

    if(cin.fail() || totalProcess <= 0){
        cin.clear();
        cin.ignore();
        goto processInput;
    }

    resourceInput:
    cout << "Enter total number of resources: ";
    cin >> totalResource;

    if(cin.fail() || totalResource <= 0){
        cin.clear();
        cin.ignore();
        goto resourceInput;
    }

    //MAX Need
    int maximum[totalProcess][totalResource];
    for(int i=0; i<totalProcess; i++){
        for(int j=0; j<totalResource; j++){
            maxInput:
            cout << "Enter Max need of resource type " << j+1 << " for process number " << i+1 << ": ";
            cin >> maximum[i][j];

            if(maximum[i][j] < 0 || cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Invalid Input! ";
                goto maxInput;
            }
        }
    }

    //Allocation
    int allocation[totalProcess][totalResource];
    for(int i=0; i<totalProcess; i++){
        for(int j=0; j<totalResource; j++){
            allocInput:
            cout << "Enter Allocated resources of type " << j+1 << " for process number " << i+1 << ": ";
            cin >> allocation[i][j];

            if(allocation[i][j] < 0 || cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Invalid Input! ";
                goto allocInput;
            }

            if(allocation[i][j] > maximum[i][j]){
                cout << endl;
                cout << "Cannot allocate more resources than maximum need!" << endl;
                goto allocInput;
            }
        }
    }

    //Need
    int need[totalProcess][totalResource];
    for(int i=0; i<totalProcess; i++){
        for(int j=0; j<totalResource; j++){
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    //Available Resource Input
    int availableResource[totalResource];
    int availableResource2[totalResource];
    for(int i=0; i<totalResource; i++){
        availableResourceInput:
        cout << "Enter total number of available resources of type " << i+1 <<": ";
        cin >> availableResource[i];

        if(cin.fail() || availableResource[i] < 0){
            cin.clear();
            cin.ignore();
            goto availableResourceInput;
        }
        availableResource2[i] = availableResource[i];
    }

    bool finish[totalProcess];
    for(int i; i<totalProcess; i++){
        finish[i] = false;
    }

    int sequence[totalProcess];
    int sequenceCount = 0;

    for(int r=0; r<totalProcess; r++){
        for(int i=0; i<totalProcess; i++){
            int complete = 0;
            for(int j=0; j<totalResource; j++){
                if(finish[i] == true){
                    break;
                }
                if(need[i][j] <= availableResource[j]){
                    complete++;
                }
            }
            if(complete == totalResource){
                finish[i] = true;
                sequence[sequenceCount] = i + 1;
                sequenceCount++;

                for(int k=0; k<totalResource; k++){
                    availableResource[k] += allocation[i][k];
                }

                cout << "P" << i+1 << " ran!" << endl;
                cout << "Available: ";
                for(int m=0;m<totalResource;m++){
                    cout << availableResource[m] << " ";
                }
                cout << endl;
            }
        }
    }

    bool deadlock = false;
    for(int i=0; i<totalProcess; i++){
        if(finish[i] == false){
            deadlock = true;
        }
    }

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "    Resource Type |" << " Max |" <<  " Allocation |" << " Need " << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for(int i=0; i<totalProcess; i++){
        for(int j=0; j<totalResource; j++){
            cout << "P" << i+1 << "  " << j+1 << "               " << maximum[i][j] << "     " << allocation[i][j] << "            " << need[i][j] << endl;
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------" << endl;

    if(!deadlock){
        cout << "Safe Sequence is: ";
        for(int i=0; i<sequenceCount; i++){
            if(i == sequenceCount-1){
                cout << "P" << sequence[i];
            } else {
                cout << "P" << sequence[i] << " --> ";
            }
        }

        cout << endl;
        processNumberInput:
        cout << "Enter the process number for resource request: ";
        int processNumber;
        cin >> processNumber;

        if(processNumber <= 0 || processNumber > totalProcess || cin.fail()){
            cin.clear();
            cin.ignore();
            cout << "Invalid Input!" << endl;
            goto processNumberInput;
        }

        for(int i=0; i<totalResource; i++){
            resourceRequestInput:
            int temp;
            cout << "Enter request for resource type " << i+1 << " for process number " << processNumber << ": ";
            cin >> temp;

            if(temp < 0 || cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Invalid Input! " << endl;
                goto resourceRequestInput;
            }

            if(temp > need[processNumber-1][i]){
                cout << "Cannot allocate more than max need! " << endl;
                goto resourceRequestInput;
            }

            allocation[processNumber-1][i] = allocation[processNumber-1][i] + temp;
            need[processNumber-1][i] = need[processNumber-1][i] - temp;
            availableResource2[i] = availableResource2[i] - temp;
        }

        bool finish2[totalProcess];
        for(int i; i<totalProcess; i++){
            finish2[i] = false;
        }

        int sequence2[totalProcess];
        int sequenceCount2 = 0;

        for(int r=0; r<totalProcess; r++){
            for(int i=0; i<totalProcess; i++){
                int complete2 = 0;
                for(int j=0; j<totalResource; j++){
                    if(finish2[i] == true){
                        break;
                    }
                    if(need[i][j] <= availableResource2[j]){
                        complete2++;
                    }
                }
                if(complete2 == totalResource){
                    finish2[i] = true;
                    sequence2[sequenceCount2] = i + 1;
                    sequenceCount2++;

                    for(int k=0; k<totalResource; k++){
                        availableResource2[k] += allocation[i][k];
                    }

                    cout << "P" << i+1 << " ran!" << endl;
                    cout << "Available: ";
                    for(int m=0;m<totalResource;m++){
                        cout << availableResource2[m] << " ";
                    }
                    cout << endl;
                }
            }
        }

        bool deadlock2 = false;
        for(int i=0; i<totalProcess; i++){
            if(finish2[i] == false){
                deadlock2 = true;
            }
        }

        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "    Resource Type |" << " Max |" <<  " Allocation |" << " Need " << endl;
        cout << "--------------------------------------------------------------------------------" << endl;

        for(int i=0; i<totalProcess; i++){
            for(int j=0; j<totalResource; j++){
                cout << "P" << i+1 << "  " << j+1 << "               " << maximum[i][j] << "     " << allocation[i][j] << "            " << need[i][j] << endl;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------------------" << endl;

        if(!deadlock2){
            cout << "Safe Sequence is: ";
            for(int i=0; i<sequenceCount2; i++){
                if(i == sequenceCount2-1){
                    cout << "P" << sequence2[i];
                } else {
                    cout << "P" << sequence2[i] << " --> ";
                }
            }
        } else {
            cout << "Deadlock occurred! One or more processes failed to run!";
        }
        cout << endl;

    } else {
        cout << "Deadlock occurred! One or more processes failed to run!";
    }
    cout << endl;

    return 0;
}
