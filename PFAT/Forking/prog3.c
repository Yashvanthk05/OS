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
		execl("/bin/ls","ls",NULL);
	}else{
		wait(NULL);
	}
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		execle("/bin/ls","ls",NULL,NULL);
	}else{
		wait(NULL);
	}
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		execlp("/bin/ls","ls",NULL);
	}else{
		wait(NULL);
	}
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		char *args[]={"ls",NULL};
		execv("/bin/ls",args);
	}else{
		wait(NULL);
	}
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}else if(pid==0){
		char *args[]={"ls",NULL};
		execvp("/bin/ls",args);
	}else{
		wait(NULL);
	}
	return 0;
}
