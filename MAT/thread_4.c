#include<stdio.h>
#include<pthread.h>

void* func(void* arg){
	int num=*(int*)arg;
	int sum=0;
	for(int i=1;i<=num;i++){
		sum+=i;
	}
	printf("Sum of %d is:%d\n",num,sum);
}

int main(){
	pthread_t thread;
	int num;
	scanf("%d",&num);
	pthread_create(&thread,NULL,func,(void*)&num);
	pthread_join(thread,NULL);
	return 0;
}
