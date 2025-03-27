#include<stdio.h>
#include<pthread.h>
#include<time.h>

void* func(void *arg){
	return NULL;
}

void thread_creation(int num){
	pthread_t thread_arr[num];
	clock_t start_time,end_time;
	start_time=clock();
	for(int i=0;i<num;i++){
		pthread_create(&thread_arr[i],NULL,func,NULL);
	}
	for(int i=0;i<num;i++){
		pthread_join(thread_arr[i],NULL);
	}
	end_time=clock();
	double time=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Total time taken for %d thread is: %.4f seconds\n",num,time);
}

int main(){
	thread_creation(5000);
	thread_creation(10000);
	thread_creation(20000);
	return 0;
}
