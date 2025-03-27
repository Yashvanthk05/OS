#include<stdio.h>
#include<pthread.h>

struct personal{
	char name[20];
	char regno[20];
	int age;
};

void* func(void *arg){
	struct personal *updateP1=(struct personal*)arg;
	scanf("%s",updateP1->name);
	scanf("%s",updateP1->regno);
	scanf("%d",&updateP1->age);
}

int main(){
	struct personal P1;
	pthread_t thread;
	pthread_create(&thread,NULL,func,(void*)&P1);
	pthread_join(thread,NULL);
	printf("Name: %s\nRegister No.: %s\nAge: %d\n",P1.name,P1.regno,P1.age);
	return 0;
}
