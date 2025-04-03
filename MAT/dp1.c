#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define N 5

sem_t chopsticks[N],mutex;
int state[N];

void* philosopher(void* args){
	int id=*(int*)args;
	sem_wait(&mutex);
	while(1){
		printf("Philosopher %d is Thinking...\n",id+1);
		state[id]=1;
		printf("Philosopher %d is Hungry...\n",id+1);
		if(state[(id+1)%N]!=0 && state[(id+4)%N]!=0){
			sem_wait(&chopsticks[(id+1)%N]);
			sem_wait(&chopsticks[(id+4)%N]);
			state[id]=0;
			printf("Philosopher %d is taking Chopsticks %d and %d\n",id+1,id+1,(id+4)%N+1);
			printf("Philosopher %d is Eating...\n",id+1);
		}
		sem_post(&mutex);
		sleep(2);
		sem_wait(&mutex);
		sem_post(&chopsticks[(id+1)%N]);
		sem_post(&chopsticks[(id+4)%N]);
		printf("Philosopher %d is putting down Chopsticks %d and %d\n",id+1,id+1,(id+4)%N+1);
		state[id]=2;
		printf("Philosopher %d is Thinking...\n",id+1);
		sem_post(&mutex);
	}
}
int main(){
	sem_init(&mutex,0,1);
	pthread_t philosophers[N];
	int ids[N];
	for(int i=0;i<N;i++){
		sem_init(&chopsticks[i],0,1);
		ids[i]=i;
	}
	for(int i=0;i<N;i++){
		pthread_create(&philosophers[i],NULL,philosopher,(void*)&ids[i]);
	}
	for(int i=0;i<N;i++){
		pthread_join(philosophers[i],NULL);
	}
	return 0;
}
