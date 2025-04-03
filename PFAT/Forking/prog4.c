#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	int num;
	scanf("%d",&num);
	pid_t pid;
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		double avg=0;
		for(int i=1;i<=num;i++){
			avg+=i;
		}
		avg/=num;
		printf("Average of %d numbers by Child Process: %.2f\n",num,avg);
	}else{
		int sum=0;
		for(int i=1;i<=num;i++){
			sum+=i;
		}
		printf("Sum of %d numbers: %d\n",num,sum);
	}
	return 0;
}
