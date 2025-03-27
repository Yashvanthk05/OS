#include<stdio.h>
#include<pthread.h>

struct personal{
	char name[20];
	char surname[20];
	int age;
};

void* func(void *args){
	struct personal *p=(struct personal*)args;
	//fgets(p->name,20,stdin);
	//fgets(p->surname,20,stdin);
	scanf("%s",p->name);
	scanf("%s",p->surname);
	scanf("%d",&p->age);
}

int main(){
	pthread_t thread;
	struct personal p1;
	pthread_create(&thread,NULL,func,(void*)&p1);
	pthread_join(thread,NULL);
	printf("Name: %s\nSurname: %s\nAge: %d\n",p1.name,p1.surname,p1.age);
	return 0;
}
