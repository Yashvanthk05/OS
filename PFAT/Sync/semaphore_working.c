#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex;

void* func(void *args){
	sem_init(&mutex,0,1);
	sem_wait(&mutex);
	printf("Entered Critical Section\n");
	sleep(2);
	printf("Exiting Critical Section\n");
	sem_post(&mutex);
}

int main(){
	sem_init(&mutex,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,func,NULL);
	sleep(2);
	pthread_create(&t2,NULL,func,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
