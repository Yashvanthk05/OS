#include<stdio.h>
#include<pthread.h>

struct info{
	char name[20];
	char surname[20];
	int age;
};

void* func(void* args){
	struct info *p=(struct info*)args;
	printf("Enter your name: ");
	fgets(p->name,20,stdin);
	printf("Enter your surname: ");
	fgets(p->surname,20,stdin);
	printf("Enter your age: ");
	scanf("%d",&p->age);
}

int main(){
	struct info p;
	pthread_t thread;
	pthread_create(&thread,NULL,func,(void*)&p);
	pthread_join(thread,NULL);
	printf("Name: %s\nSurname: %s\nAge: %d\n",p.name,p.surname,p.age);
	return 0;
}
