#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_ITEMS 10
#define CONSUMERS 3

sem_t empty,full,mutex;
int count=0;
int buffer[BUFFER_ITEMS];

void* producer(void* args){
	for(int i=0;i<BUFFER_ITEMS;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		int item=rand()%100;
		buffer[count++]=item;
		printf("Producer produced %d\n",item);
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}

void* consumer(void* args){
	int id=*(int*)args;
	for(int i=0;i<3;i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[--count];
		printf("Consumer %d consumed %d\n",id,item);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
}

int main(){
	sem_init(&empty,1,BUFFER_ITEMS);
	sem_init(&full,1,0);
	sem_init(&mutex,0,1);
	pthread_t pid,cid[CONSUMERS];
	int consumer_ids[CONSUMERS]={10,20,30};
	pthread_create(&pid,NULL,producer,NULL);
	for(int i=0;i<CONSUMERS;i++){
		pthread_create(&cid[i],NULL,consumer,(void*)&consumer_ids[i]);
	}
	pthread_join(pid,NULL);
	for(int i=0;i<CONSUMERS;i++){
		pthread_join(cid[i],NULL);
	}
	return 0;
}
