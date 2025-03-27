#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* func(void *args){
	int n=*(int*)args;
	int *sum=(int*)malloc(sizeof(int));
	*sum=0;
	for(int i=1;i<=n;i++){
		*sum+=i;
	}
	pthread_exit(sum);
}	

int main(){
	int num,*sum;
	scanf("%d",&num);
	pthread_t thread;
	pthread_create(&thread,NULL,func,(void*)&num);
	pthread_join(thread,(void**)&sum);
	printf("Sum of %d numbers: %d\n",num,*sum);
	return 0;
}
