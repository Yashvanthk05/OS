#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<sched.h>
#include<signal.h>

#define STACK_SIZE (1024*1024)

int child_func(void* args){
	return 0;
}

int main(){
	clock_t start_time,end_time;
	pid_t pid;
	start_time=clock();
	for(int i=0;i<10000;i++){
		pid=vfork();
		if(pid<0){
			exit(1);
		}else if(pid==0){
			_exit(0);
		}
	}
	end_time=clock();
	double time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time Taken by 50K vfork process: %.4f seconds\n",time_taken);
	start_time=clock();
	for(int i=0;i<10000;i++){
		char *child_stack;
		child_stack=(char*)malloc(STACK_SIZE);
		pid=clone(child_func,child_stack+STACK_SIZE,SIGCHLD,NULL);
		if(pid<0){
			perror("Clone Failed");
			exit(1);
		}
	}
	end_time=clock();
	time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time taken for 50K Clone Process: %.4f\n",time_taken);
	return 0;
}
