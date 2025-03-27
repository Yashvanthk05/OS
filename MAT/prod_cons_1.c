#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>


sem_t empty,full,mutex;
int data;

void* producer(void *args){
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		data=rand()%100;
		printf("Producer produced %d\n",data);
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}
	
void* consumer(void *args){
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		printf("Consumer consumed %d\n",data);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
}

int main(){
	sem_init(&empty,1,1);
	sem_init(&full,1,0);
	sem_init(&mutex,0,1);
	pthread_t pid,cid;
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	return 0;
}
