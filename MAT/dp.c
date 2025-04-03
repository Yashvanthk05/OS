#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define N 5

sem_t chopsticks[N];
sem_t mutex;
int state[N];

void* philosopher(void *args){
	int id=*(int*)args;
	while(1){
		printf("Philosopher %d is Thinking...\n",id+1);
		sleep(rand()%3);
		sem_wait(&mutex);
		state[id]=1;
		printf("Philosopher %d is Hungry...\n",id+1);
		if(state[(id+1)%N]!=0 && state[(id+4)%N]!=0){
			state[id]=0;
			sem_wait(&chopsticks[id]);
			sem_wait(&chopsticks[(id+1)%N]);
			printf("Philosopher %d taking chopsticks %d and %d\n",id+1,id+1,(id+4)%N+1);
			printf("Philosopher %d is Eating...\n",id+1);
		}
		sem_post(&mutex);
		sleep(2);
		sem_wait(&mutex);
		state[id]=2;
		sem_post(&chopsticks[id]);
		sem_post(&chopsticks[(id+1)%N]);
		printf("Philosopher %d is putting chopsticks %d and %d\n",id+1,id+1,(id+4)%N+1);
		printf("Philosopher %d is thinking...\n",id+1);
		sem_post(&mutex);
	}
}
		

int main(){
	pthread_t philosophers[N];
	int ids[N];
	sem_init(&mutex,0,1);
	for(int i=0;i<N;i++){
		ids[i]=i;
		sem_init(&chopsticks[i],0,1);
	}
	for(int i=0;i<N;i++){
		pthread_create(&philosophers[i],NULL,philosopher,(void*)&ids[i]);
	}
	for(int i=0;i<N;i++){
		pthread_join(philosophers[i],NULL);
	}
	return 0;
}

