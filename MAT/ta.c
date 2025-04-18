#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_STUDENTS 10
#define WAITING_CHAIRS 3

sem_t sem_ta,sem_stu;
pthread_mutex_t mutex;
int waiting_students=0;


void* ta_func(void* args){
	while(1){
		sem_wait(&sem_stu);
		pthread_mutex_lock(&mutex);
		if(waiting_students>0){
			waiting_students--;
			printf("TA is helping a Student. Waiting Students: %d\n",waiting_students);
			sem_post(&sem_ta);
		}else{
			printf("No Students Waiting..\n");
		}
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
}

void* student_func(void* args){
	int id=*(int*)args;
	sleep(rand()%5);
	pthread_mutex_lock(&mutex);
	if(waiting_students<WAITING_CHAIRS){
		waiting_students++;
		printf("Student %d is waiting. Waiting Student: %d\n",id,waiting_students);
		sem_post(&sem_stu);
		pthread_mutex_unlock(&mutex);
		sem_wait(&sem_ta);
		printf("Student %d is getting help from TA\n",id);
	}else{
		printf("Student %d finds no seat and will return later.\n",id);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	pthread_t students[NUM_STUDENTS],ta;
	int student_ids[NUM_STUDENTS];
	sem_init(&sem_ta,0,0);
	sem_init(&sem_stu,0,0);
	pthread_create(&ta,NULL,ta_func,NULL);
	for(int i=0;i<NUM_STUDENTS;i++){
		student_ids[i]=i+1;
		pthread_create(&students[i],NULL,student_func,(void*)&student_ids[i]);
	}
	for(int i=0;i<NUM_STUDENTS;i++){
		pthread_join(students[i],NULL);
	}
	return 0;
}
