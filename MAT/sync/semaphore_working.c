#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex;

void* func(void *args){
	sem_wait(&mutex);
	printf("Entered Critical Section...\n");
	sleep(2);
	printf("Exiting Critical Section...\n");
	sem_post(&mutex);
}

int main(){
	sem_init(&mutex,0,1);
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,func,NULL);
	pthread_create(&thread2,NULL,func,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	sem_destroy(&mutex);
	return 0;
}

