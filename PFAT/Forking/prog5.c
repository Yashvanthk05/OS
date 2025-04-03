#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<sched.h>
#include<time.h>

#define STACK_SIZE 1024*1024

int child_func(void* args){
	return 0;
}

int main(){
	pid_t pid;
	clock_t start_time,end_time;
	
	start_time=clock();
	for(int i=0;i<5000;i++){
		pid=vfork();
		if(pid<0){
			fprintf(stderr,"Fork Failed\n");
			exit(1);
		}else if(pid==0){
			_exit(0);
		}
	}
	end_time=clock();
	double time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time taken for vforking 5000 process: %.4f\n",time_taken);
	start_time=clock();
	for(int i=0;i<5000;i++){
		char *child_stack=(char*)malloc(STACK_SIZE);
		pid=clone(child_func,child_stack+STACK_SIZE,SIGCHLD,NULL);
		if(pid<0){
			fprintf(stderr,"Cloning failed\n");
			exit(1);
		}
	}
	end_time=clock();
	time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time taken for cloning 5000 process: %.4f\n",time_taken);
	return 0;
}
