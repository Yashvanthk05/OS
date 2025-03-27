#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define BUFFER_ITEMS 5

int buffer[BUFFER_ITEMS];
int in=0;
int out=0;
int producedcount=0;
int consumedcount=0;
sem_t empty,full,mutex;

void* producer(void *args){
	int item=1;
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=item;
		item++;
		producedcount++;
		printf("Produced Item: %d\n",buffer[in]);
		in=(in+1)%BUFFER_ITEMS;
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
	return NULL;
}

void* consumer(void *args){
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[out];
		out=(out+1)%BUFFER_ITEMS;
		consumedcount++;
		printf("Consumed Item: %d\n",item);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
	return NULL;
}

int main(){
	sem_init(&empty,1,BUFFER_ITEMS);
	sem_init(&full,1,0);
	sem_init(&mutex,1,1);
	pthread_t pid,cid;
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	return 0;
}
