#include<stdio.h>
#include<stdbool.h>

void print_matrix(int p,int r,int matrix[p][r]){
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void isSafe(int p,int r,int avail[r],int need[p][r],int alloc[p][r]){
    int finish[p],safe_seq[p],work[r];
    for(int i=0;i<p;i++){
        finish[i]=0;
    }
    for(int i=0;i<r;i++){
        work[i]=avail[i];
    }
    int count=0,index=0;
    while(count<p){
        bool found=false;
        for(int i=0;i<p;i++){
            bool canAllocate=true;
            if(finish[i]==0){
                for(int j=0;j<r;j++){
                    if(need[i][j]>work[j]){
                        canAllocate=false;
                        break;
                    }
                }
            }
            if(canAllocate){
                found=true;
                count++;
                safe_seq[index++]=i;
                finish[i]=1;
                printf("Process %d is allocated\n",i);
                for(int j=0;j<r;j++){
                    work[j]+=alloc[i][j];
                }
            }
        }
        if(!found){
            printf("System is not in a safe state\n");
            printf("Deadlock detected\n");
            printf("Safe Sequence: ");
            for(int i=0;i<index;i++){
                printf("%d ",safe_seq[i]);
            }
            printf("\n");
        }
    }
    printf("System is in a safe state\n");
    printf("Safe Sequence: ");
    for(int i=0;i<p;i++){
        printf("%d ",safe_seq[i]);
    }
    printf("\n");
}

int main(){
    int p,r;
    printf("Enter the Number of Processes and Resources:\n");
    scanf("%d %d",&p,&r);
    int alloc[p][r],max[p][r],need[p][r],avail[r],total_alloc[r],max_instances[r];
    printf("Enter the Maximum Instances for each resource:\n");
    for(int i=0;i<r;i++){
        scanf("%d",&max_instances[i]);
        total_alloc[i]=0;
    }
    printf("Enter Allocation Matrix:\n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            total_alloc[j]+=alloc[i][j];
        }
    }
    printf("Total Allocation Matrix:\n");
    for(int i=0;i<r;i++){
        printf("%d ",total_alloc[i]);
    }
    printf("\n");
    printf("Enter Max Matrix:\n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }
    for(int i=0;i<r;i++){
        avail[i]=max_instances[i]-total_alloc[i];
    }
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("Available Matrix:\n");
    for(int i=0;i<r;i++){
        printf("%d ",avail[i]);
    }
    printf("\n");
    printf("Allocation Matrix:\n");
    print_matrix(p,r,alloc);
    printf("Max Matrix:\n");
    print_matrix(p,r,max);
    printf("Need Matrix:\n");
    print_matrix(p,r,need);
    isSafe(p,r,avail,need,alloc);
    int request[r],proc_req;;
    printf("Enter Process No for Request:");
    scanf("%d",&proc_req);
    printf("Enter Request Vector:\n");
    for(int i=0;i<r;i++){
        scanf("%d",&request[i]);
    }
    for(int i=0;i<r;i++){
        if(request[i]>need[proc_req][i]){
            printf("Error: Process has exceeded its maximum claim\n");
            return 0;
        }
        if(request[i]>avail[i]){
            printf("Process is waiting\n");
            return 0;
        }
    }
    for(int i=0;i<r;i++){
        avail[i]-=request[i];
        alloc[proc_req][i]+=request[i];
        need[proc_req][i]-=request[i];
    }
    isSafe(p,r,avail,need,alloc);
    for(int i=0;i<r;i++){
        avail[i]+=request[i];
        alloc[proc_req][i]-=request[i];
        need[proc_req][i]+=request[i];
    }
    return 0;
}