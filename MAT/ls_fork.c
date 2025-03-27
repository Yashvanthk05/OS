#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		execlp("/bin/ls","ls",NULL);
		printf("List of Directory");
	}else{
		wait(NULL);
	}
	return 0;
}
