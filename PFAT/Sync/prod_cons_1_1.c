#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_ITEMS 10

sem_t empty,full,mutex;
int in=0,out=9,producedcount=0,consumedcount=0;
int buffer[BUFFER_ITEMS];

void* producer(void* args){
	int item=1;
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=item;
		item++;
		producedcount++;
		printf("Producer produced Item %d. Produced Count: %d\n",buffer[in],producedcount);
		in=(in+1)%BUFFER_ITEMS;
		sem_post(&mutex);
		sem_post(&full);
		sleep(rand()%3);
	}
}

void* consumer(void* args){
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[out];
		out=(out+1)%BUFFER_ITEMS;
		consumedcount++;
		printf("Consumer consumed Item %d. Consumed Count: %d\n",buffer[out],consumedcount);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(rand()%3);
	}
}

int main(){
	pthread_t pid,cid;
	sem_init(&empty,1,BUFFER_ITEMS);
	sem_init(&full,1,0);
	sem_init(&mutex,1,1);
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	return 0;
}
