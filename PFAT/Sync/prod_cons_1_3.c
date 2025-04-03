#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 10
#define NUM_CONSUMERS 3

sem_t empty,full,mutex;
int in=0,out=0,producedcount=0,consumedcount=0;
int buffer[N];

void* producer(void* args){
	int item=1;
	for(int i=0;i<N;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=item;
		item++;
		producedcount++;
		printf("Producer produced Item %d. Produced Count: %d\n",buffer[in],producedcount);
		in=(in+1)%N;
		sem_post(&mutex);
		sem_post(&full);
		sleep(rand()%3);
	}
}

void* consumer(void* args){
	int id=*(int*)args;
	for(int i=0;i<(int)(N/NUM_CONSUMERS);i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[out];
		consumedcount++;
		printf("Consumer %d consumed Item %d. Consumed Count: %d\n",id,item,consumedcount);
		out=(out+1)%N;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(rand()%3);
	}
}

int main(){
	sem_init(&empty,1,N);
	sem_init(&full,1,0);
	sem_init(&mutex,1,1);
	pthread_t pid,cid[NUM_CONSUMERS];
	pthread_create(&pid,NULL,producer,NULL);
	for(int i=0;i<NUM_CONSUMERS;i++){
		int *id=(int*)malloc(sizeof(int));
		*id=i+1;
		pthread_create(&cid[i],NULL,consumer,(void*)id);
	}
	pthread_join(pid,NULL);
	for(int i=0;i<NUM_CONSUMERS;i++){
		pthread_join(cid[i],NULL);
	}
	return 0;
}
