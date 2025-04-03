#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

void* func(void* args){
	return NULL;
}

void threadcreation(int n){
	clock_t start_time,end_time;
	pthread_t threads[n];
	start_time=clock();
	for(int i=0;i<n;i++){
		pthread_create(&threads[i],NULL,func,NULL);
	}
	for(int i=0;i<n;i++){
		pthread_join(threads[i],NULL);
	}
	end_time=clock();
	double time_taken=(double)(end_time-start_time)/CLOCKS_PER_SEC;
	printf("Time Taken for %d threads: %.6f seconds\n",n,time_taken);
}

int main(){
	threadcreation(5000);
	threadcreation(10000);
	threadcreation(20000);
	return 0;
}
	
