#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void* func(void *arg){
	pthread_mutex_lock(&mutex);
	counter++;
	printf("Count: %d\n",counter);
	pthread_mutex_unlock(&mutex);
}

int main(){
	pthread_t thread1,thread2;
	int rc1=pthread_create(&thread1,NULL,func,NULL);
	if(rc1){
		fprintf(stderr,"Pthread1 creation failed\n");
	}
	int rc2=pthread_create(&thread2,NULL,func,NULL);
	if(rc2){
		fprintf(stderr,"Pthread2 creation failed\n");
	}
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}
