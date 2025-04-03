#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void* func(void* args){
	pthread_mutex_lock(&mutex);
	counter++;
	printf("Counter Value: %d\n",counter);
	pthread_mutex_unlock(&mutex);
}

int main(){
	pthread_t thread1,thread2;
	int rc1,rc2;
	rc1=pthread_create(&thread1,NULL,func,NULL);
	rc2=pthread_create(&thread2,NULL,func,NULL);
	if(rc1){
		fprintf(stderr,"Thread Creation Failed: %d\n",rc1);
	}
	if(rc2){
		fprintf(stderr,"Thread Creation Failed: %d\n",rc2);
	}
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}
