#include<stdio.h>
#include<unistd.h>

int main(){
	printf("%d is the Process ID",(int)getpid());
	printf("%d is the Parent Process ID",getppid());
	return 0;
}
