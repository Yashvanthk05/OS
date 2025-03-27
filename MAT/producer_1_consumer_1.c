#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_SIZE 5

sem_t empty;
sem_t full;
sem_t mutex;

int count=0;
int buffer[BUFFER_SIZE];

void* producer(void* args){
	int item=1;
	for(int i=0;i<BUFFER_SIZE;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[i]=item;
		count++;
		printf("Producer produced %d item\n",i);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void* consumer(void *args){
	for(int i=0;i<BUFFER_SIZE;i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[--count];
		printf("Consumer consumed %d item\n",item);
		sem_post(&mutex);
		sem_post(&empty);
	}
}
		

int main(){
	sem_init(&empty,1,BUFFER_SIZE);
	sem_init(&full,1,0);
	sem_init(&mutex,0,1);
	pthread_t pid,cid;
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	return 0;
}
