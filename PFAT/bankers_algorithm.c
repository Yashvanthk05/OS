#include<stdio.h>
#include<stdbool.h>

void isSafe(int p,int r,int alloc[p][r],int need[p][r],int avail[r]){
	int finish[p],safe_seq[p],index=0,work[r],completed=0;
	for(int i=0;i<r;i++){
		work[i]=avail[i];
	}
	for(int i=0;i<p;i++){
		finish[i]=0;
	}
	while(completed<p){
		bool found=false;
		for(int i=0;i<p;i++){
			if(finish[i]==0){
				bool canAllocate=true;
				for(int j=0;j<r;j++){
					if(need[i][j]>work[j]){
						canAllocate=false;
						break;
					}
				}
				if(canAllocate){
					finish[i]=1;
					found=true;
					safe_seq[index++]=i;
					for(int j=0;j<r;j++){
						work[j]+=alloc[i][j];
					}
					completed++;
				}
			}
		}
		if(!found){
			printf("System is in Dealock");
			return;
		}
	}
	printf("System is in Safe State\nSafe Sequence: ");
	for(int i=0;i<p;i++){
		printf("%d ",safe_seq[i]);
	}		
}

void printmatrix(int p,int r,int matrix[p][r]){
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}

void printvector(int n,int vector[]){
	for(int i=0;i<n;i++){
		printf("%d ",vector[i]);
	}
	printf("\n");
}

int main(){
	int p,r;
	printf("Enter the Number of Processes and Resources: ");
	scanf("%d %d",&p,&r);
	int max_instances[r],max[p][r],alloc[p][r],total_alloc[r],avail[r],need[p][r];
	
	for(int i=0;i<r;i++){
		total_alloc[i]=0;
	}
	
	printf("Enter the Max Instances: ");
	for(int i=0;i<r;i++){
		scanf("%d",&max_instances[i]);
	}
	
	printf("Enter Maximum Allocation Matrix:\n");
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			scanf("%d",&max[i][j]);
		}
	}
	
	printf("Enter Allocation Matrix:\n");
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			scanf("%d",&alloc[i][j]);
			total_alloc[j]+=alloc[i][j];
		}
	}
	
	for(int i=0;i<r;i++){
		avail[i]=max_instances[i]-total_alloc[i];
	}
	
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			need[i][j]=max[i][j] -alloc[i][j];
		}
	}
	
	printf("\nMax Instances:\n");
	printvector(r,max_instances);
	
	printf("\nAllocation Matrix:\n");
	printmatrix(p,r,alloc);
	
	printf("\nMaximum Matrix:\n");
	printmatrix(p,r,max);
	
	printf("\nNeed Matrix:\n");
	printmatrix(p,r,need);
	
	printf("\nTotal Allocated Instances:\n");
	printvector(r,total_alloc);
	
	printf("\nAvailable Vector:\n");
	printvector(r,avail);
	
	isSafe(p,r,alloc,need,avail);
	
	int reqpno,req[r];
	printf("Enter the Process No for Request: ");
	scanf("%d",&reqpno);
	printf("Enter the Request Vector: ");
	for(int i=0;i<r;i++){
		scanf("%d",&req[i]);
	}
	
	for(int i=0;i<r;i++){
		if(need[reqpno][i]<req[i]){
			printf("Request Vector is Greater than Need cannot be allocated Immediately\n");
		}
		if(avail[i]<req[i]){
			printf("Request Vector is Greater than Available Vector cannot be allocated Immediately\n");
		}
	}
	
	for(int i=0;i<r;i++){
		alloc[reqpno][i]+=req[i];
		need[reqpno][i]-=req[i];
		avail[i]-=req[i];
	}
	
	isSafe(p,r,alloc,need,avail);
	
	return 0;
}		
