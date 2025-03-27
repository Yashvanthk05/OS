#include<stdio.h>
#include<pthread.h>

void* func(void* arg){
	printf("Welcome this is Yashvanth\n");
}

int main(){
	pthread_t thread;
	int rc=pthread_create(&thread,NULL,func,NULL);
	if(rc){
		printf("Error: Pthread Creation Failed\n");
		return 1;
	}
	pthread_join(thread,NULL);
	return 0;
}
