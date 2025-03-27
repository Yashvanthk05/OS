#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex;
int counter=0;

void* func(void *args){
	int id=*(int*)args;
	pthread_mutex_lock(&mutex);
	printf("Thread %d Entered Critical Section\n",id);
	counter++;
	printf("Counter Value: %d\n",counter);
	sleep(2);
	printf("Thread %d Exiting Critical Section\n",id);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	pthread_t thread1,thread2;
	int thread_id[2]={1,2};
	pthread_create(&thread1,NULL,func,(void*)&thread_id[0]);
	pthread_create(&thread2,NULL,func,(void*)&thread_id[1]);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	exit(EXIT_SUCCESS);
	return 0;
}
