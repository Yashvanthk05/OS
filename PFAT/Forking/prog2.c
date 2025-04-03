#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed\n");
		return 1;
	}else if(pid==0){
		printf("List of Directories\n");
		execlp("/bin/ls","ls",NULL);
		printf("Child Process Failed\n");
	}else{
		wait(NULL);
	}
	return 0;
}
