#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define N 5
#define LEFT (id+4)%N
#define RIGHT (id+1)%N
#define THINKING 2
#define HUNGRY 1
#define EATING 0

sem_t mutex,s[N];
int state[N];

void test(int id){
    if(state[id]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING){
        state[id]=EATING;
        sleep(2);
        printf("Philosopher %d is taking fork %d and %d\n",id+1,LEFT+1,id+1);
        printf("Philosopher %d is Eating...\n",id+1);
        sem_post(&s[id]);
    }
}

void take_fork(int id){
    sem_wait(&mutex);
    state[id]=HUNGRY;
    printf("Philosopher %d is Hungry...\n",id+1);
    test(id);
    sem_post(&mutex);
    sem_wait(&s[id]);
    sleep(1);
}

void put_fork(int id){
    sem_wait(&mutex);
    state[id]=THINKING;
    printf("Philosopher %d is dropping fork %d and %d\n",id+1,LEFT+1,id+1);
    printf("Philosopher %d is Thinking...\n",id+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* args){
    while(1){
        int id=*(int*)args;
        sleep(1);
        take_fork(id);
        sleep(0);
        put_fork(id);
    }
}

int main(){
    pthread_t philosophers[N];
    sem_init(&mutex,0,1);
    int ids[N];
    for(int i=0;i<N;i++){
        ids[i]=i;
        sem_init(&s[i],0,0);
    }
    for(int i=0;i<N;i++){
        pthread_create(&philosophers[i],NULL,philosopher,(void*)&ids[i]);
        printf("Philosopher %d is Thinking...\n",i+1);
    }
    for(int i=0;i<N;i++){
        pthread_join(philosophers[i],NULL);
    }
    return 0;
}