#include<stdio.h>
#include<pthread.h>

void* func(void* args){
	char *msg=(char*)args;
	printf("Message is: %s\n",msg);
}

int main(){
	pthread_t thread1,thread2;
	char msg[20];
	fgets(msg,20,stdin);
	pthread_create(&thread1,NULL,func,msg);
	fgets(msg,20,stdin);
	pthread_create(&thread2,NULL,func,msg);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}
