#include <stdio.h>
#include <stdbool.h>

int TOTPROC;
int TOTRES;

void calculateNeedMatrix(int need[TOTPROC][TOTRES], 
                        int max[TOTPROC][TOTRES], 
                        int allocation[TOTPROC][TOTRES], 
                        int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void printMatrix(int matrix[TOTPROC][TOTRES], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < resources; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printVector(int vector[], int resources){
    for (int i = 0; i < resources; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

bool isSafe(int processes, int resources, int available[], int max[][TOTRES], 
           int allocation[][TOTRES], int need[][TOTRES], int safeSeq[]) {
    
    bool finish[TOTPROC];
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }
    
    int work[TOTRES];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    
    int count = 0;
    while (count < processes) {
        bool found = false;   
        for (int i = 0; i < processes; i++) {
            if (finish[i] == false) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }           
                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (found == false) {
            return false;
        }
    }
    
    return true;
}

bool requestResources(int process, int request[], int processes, int resources,
                     int available[], int max[][TOTRES], 
                     int allocation[][TOTRES], int need[][TOTRES], int safeSeq[]) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim\n");
            return false;
        }
    }
    for (int i = 0; i < resources; i++) {
        if (request[i] > available[i]) {
            printf("Resources not available, process must wait\n");
            return false;
        }
    }
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    if (isSafe(processes, resources, available, max, allocation, need, safeSeq)) {
        printf("Request can be granted immediately\n");
        return true;
    } else {
        printf("Request results in unsafe state, cannot be granted\n");
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }
}

int main() {
    int processes, resources;
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    TOTPROC = processes;
    
    printf("Enter number of resource types: ");
    scanf("%d", &resources);
    TOTRES = resources;
    
    int available[TOTRES];
    int max[TOTPROC][TOTRES];
    int allocation[TOTPROC][TOTRES];
    int need[TOTPROC][TOTRES];
    int total[TOTRES];
    int safeSeq[TOTPROC];
    
    printf("Enter the max instances:\n");
    for (int i = 0; i < resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &total[i]);
    }
    
    printf("\nEnter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        printf("For Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("\nEnter the Max Matrix:\n");
    for (int i = 0; i < processes; i++) {
        printf("For Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    for (int i = 0; i < resources; i++) {
        int sum = 0;
        for (int j = 0; j < processes; j++) {
            sum += allocation[j][i];
        }
        available[i] = total[i] - sum;
    }
    
    calculateNeedMatrix(need, max, allocation, processes, resources);
    
    printf("\nAllocation Matrix:\n");
    printMatrix(allocation, processes, resources);
    
    printf("\nMax Matrix:\n");
    printMatrix(max, processes, resources);
    
    printf("\nNeed Matrix:\n");
    printMatrix(need, processes, resources);
    
    printf("\nAvailable Vector:\n");
    printVector(available, resources);
    
    if (isSafe(processes, resources, available, max, allocation, need, safeSeq)) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < processes; i++) {
            printf("P%d ", safeSeq[i]);
            if (i < processes - 1) {
                printf("-> ");
            }
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a SAFE state.\n");
    }
    
    char choice;
    printf("\nEnter a resource request? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        int process;
        int request[TOTRES];
        
        printf("Enter the process ID(0-%d): ", processes - 1);
        scanf("%d", &process);
        
        printf("Enter the request vector:\n");
        for (int i = 0; i < resources; i++) {
            printf("Resource %d: ", i);
            scanf("%d", &request[i]);
        }
        
        int tempAvailable[TOTRES];
        int tempAllocation[TOTPROC][TOTRES];
        int tempNeed[TOTPROC][TOTRES];
        
        for(int i = 0; i < resources; i++) {
            tempAvailable[i] = available[i];
        }
        
        for(int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                tempAllocation[i][j] = allocation[i][j];
                tempNeed[i][j] = need[i][j];
            }
        }
        
        if(requestResources(process, request, processes, resources, available, max, allocation, need, safeSeq)) {
            printf("Updated Available Vector: ");
            for(int i = 0; i < resources; i++){
                printf("%d ", available[i]);
            }
            printf("\n");
            
            printf("Safe Sequence after allocation: ");
            for(int i = 0; i < processes; i++){
                printf("P%d ", safeSeq[i]);
                if(i < processes - 1){
                    printf("-> ");
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}
