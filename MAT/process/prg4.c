#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#include<unistd.h>

int main(){
	int num;
	scanf("%d",&num);
	int avg=0;
	unsigned long long int fac=1;
	pid_t pid;
	pid=fork();
	clock_t start_time,end_time;
	start_time=clock();
	if(pid<0){
		fprintf(stderr,"Fork Failed\n");
		return 1;
	}else if(pid==0){
		for(int i=1;i<=num;i++){
			avg+=i;
		}
		printf("Child Process: Average till %d numbers: %.2f\n",num,(float)avg/num);
	}else{
		wait(NULL);
		for(int i=1;i<=num;i++){
			fac*=i;
		}
		printf("Parent Process: Factorial of %d: %llu\n",num,fac);
	}
	end_time=clock();
	double time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Total Execution Time : %.4f\n",time_taken);
	return 0;
}
