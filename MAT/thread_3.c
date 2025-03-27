#include<stdio.h>
#include<pthread.h>

void* func(void* arg){
	printf("%s ",(char*)arg);
}

int main(){
	pthread_t thread1,thread2;
	char *msg1="Yashvanth";
	pthread_create(&thread1,NULL,func,(void*)"Yashvanth");
	pthread_create(&thread2,NULL,func,(void*)"Karunakaran");
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}
