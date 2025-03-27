#include<stdio.h>
#include<pthread.h>

void* func(void* args){
	printf("Welcome to Yashvanth World\n");
}

int main(){
	pthread_t thread;
	pthread_create(&thread,NULL,func,NULL);
	pthread_join(thread,NULL);
	return 0;
}
