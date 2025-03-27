#include<stdio.h>
#include<pthread.h>
#include<time.h>

void* func(void *args){
	return NULL;
}

void thread_creation(int num){
	clock_t start_time,end_time;
	pthread_t thread[num];
	start_time=clock();
	for(int i=0;i<num;i++){
		pthread_create(&thread[i],NULL,func,NULL);
	}
	for(int i=0;i<num;i++){
		pthread_join(thread[i],NULL);
	}
	end_time=clock();
	double time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time taken for %d thread creation: %.4f seconds\n",num,time_taken);
}

int main(){
	thread_creation(5000);
	thread_creation(10000);
	thread_creation(20000);
	return 0;
}
