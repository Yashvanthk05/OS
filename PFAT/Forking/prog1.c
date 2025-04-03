#include<stdio.h>
#include<unistd.h>

int main(){
	printf("Current Process Identifier: %d\n",(int)getpid());
	printf("Parent Process Identifier: %d\n",(int)getppid());
	return 0;
}
