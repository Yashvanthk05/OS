#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_ITEMS 10
#define CONSUMERS 3

int buffer[BUFFER_ITEMS];
int producedcount=0;
int consumedcount=0;
int in=0;
int out=0;
sem_t empty,full,mutex;

void* producer(void *args){
	int item=1;
	for(int i=0;i<BUFFER_ITEMS;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=item;
		item++;
		printf("Produced %d\n",buffer[in]);
		in=(in+1)%BUFFER_ITEMS;
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
	return NULL;
}

void* consumer(void *args){
	int id=*(int*)args;
	for(int i=0;i<(int)(BUFFER_ITEMS/CONSUMERS);i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[out];
		out=(out+1)%BUFFER_ITEMS;
		printf("Consumer %d Consumed %d\n",id,item);
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
	pthread_t pid,cid[CONSUMERS];
	pthread_create(&pid,NULL,producer,NULL);
	for(int i=0;i<CONSUMERS;i++){
		int *id=(int*)malloc(sizeof(int));
		*id=i+1;
		pthread_create(&cid[i],NULL,consumer,(void*)id);
	}
	pthread_join(pid,NULL);
	for(int i=0;i<CONSUMERS;i++){
		pthread_join(cid[i],NULL);
	}
	return 0;
}
