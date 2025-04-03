#include<stdio.h>
#include<pthread.h>

void* func(void* args){
	int num=*(int*)args;
	int sum=0;
	for(int i=1;i<=num;i++){
		sum+=i;
	}
	printf("Sum of %d numbers: %d\n",num,sum);
}

int main(){
	int n;
	scanf("%d",&n);
	pthread_t thread;
	pthread_create(&thread,NULL,func,(void*)&n);
	pthread_join(thread,NULL);
	return 0;
}
