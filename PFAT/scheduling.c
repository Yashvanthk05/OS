#include<stdio.h>
#include<limits.h>

typedef struct Process{
	int pid,at,bt,rt,ct,tat,wt,p;
}Process;

void FCFS(Process p[],int n){
	int completed=0,time=0;
	while(completed<n){
		int minindex=-1;
		int min_at=INT_MAX;
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].at<min_at && p[i].rt>0){
				minindex=i;
				min_at=p[i].at;
			}
		}
		if(minindex==-1){
			time++;
		}else{
			time+=p[minindex].rt;
			p[minindex].rt=0;
			p[minindex].ct=time;
			completed++;
		}
	}
}

void SJF(Process p[],int n){
	int completed=0,time=0;
	while(completed<n){
		int minindex=-1;
		int min_rt=INT_MAX;
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].rt>0 && p[i].rt<min_rt){
				minindex=i;
				min_rt=p[i].bt;
			}
		}
		if(minindex==-1){
			time++;
		}else{
			time+=p[minindex].rt;
			p[minindex].rt=0;
			p[minindex].ct=time;
			completed++;
		}
	}
}

void SRTF(Process p[],int n){
	int completed=0,time=0;
	while(completed<n){
		int minindex=-1;
		int min_rt=INT_MAX;
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].rt>0 && p[i].rt<min_rt){
				minindex=i;
				min_rt=p[i].rt;
			}
		}
		if(minindex==-1){
			time++;
		}else{
			time++;
			p[minindex].rt--;
			if(p[minindex].rt==0){
				p[minindex].ct=time;
				completed++;
			}
		}
	}
}

void NONPREMP(Process p[],int n){
	int completed=0,time=0;
	while(completed<n){
		int minindex=-1;
		int min_p=INT_MAX;
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].rt>0 && p[i].p<min_p){
				minindex=i;
				min_p=p[i].p;
			}
		}
		if(minindex==-1){
			time++;
		}else{
			time+=p[minindex].rt;
			p[minindex].rt=0;
			p[minindex].ct=time;
			completed++;
		}
	}
}

void PREMP(Process p[],int n){
	int completed=0,time=0;
	while(completed<n){
		int minindex=-1;
		int min_p=INT_MAX;
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].rt>0 && p[i].p<min_p){
				minindex=i;
				min_p=p[i].p;
			}
		}
		if(minindex==-1){
			time++;
		}else{
			time++;
			p[minindex].rt--;
			if(p[minindex].rt==0){
				p[minindex].ct=time;
				completed++;
			}
		}
	}
}

void ROUND_ROBBIN(Process p[],int n){
	int completed=0,time=0,quantum;
	printf("Enter the Quantum: ");
	scanf("%d",&quantum);
	while(completed<n){
		for(int i=0;i<n;i++){
			if(p[i].at<=time && p[i].rt>0){
				int executetime=(p[i].rt>quantum)?quantum:p[i].rt;
				time+=executetime;
				p[i].rt-=executetime;
				if(p[i].rt==0){
					p[i].ct=time;
					completed++;
				}
			}
		}
	}
}

int main(){
	int n;
	printf("Enter the Number of Processes: ");
	scanf("%d",&n);
	Process p[n];
	printf("Enter the Arrival Time, Burst Time, Priority:\n");
	for(int i=0;i<n;i++){
		scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].p);
		p[i].pid=i;
	}
	int choice;
	do{
		printf("1. FCFS\n2. NON PREMPTIVE PRIORITY\n3. SJF\n4. SRTF\n5. PREMPTIVE PRIORITY\n6. ROUND ROBBIN\n7. EXIT\nEnter the Choice: ");
		scanf("%d",&choice);
		if(choice==7) break;
		for(int i=0;i<n;i++){
			p[i].rt=p[i].bt;
			p[i].tat=p[i].ct=p[i].wt=0;
		}
		if(choice==1) FCFS(p,n);
		else if(choice==2) NONPREMP(p,n);
		else if(choice==3) SJF(p,n);
		else if(choice==4) SRTF(p,n);
		else if(choice==5) PREMP(p,n);
		else if(choice==6) ROUND_ROBBIN(p,n);
		else{
			printf("Invalid Choice\n");
			continue;
		}
		double avgwt=0,avgtat=0;
		for(int i=0;i<n;i++){
			p[i].tat=p[i].ct-p[i].at;
			p[i].wt=p[i].tat-p[i].bt;
			avgwt+=p[i].wt;
			avgtat+=p[i].tat;
		}
		avgwt/=n;
		avgtat/=n;
		printf("Process\tArrival(ms)\tBurst(ms)\tPriority\tCompletion(ms)\tTurnAround(ms)\tWaiting(ms)\n");
		for(int i=0;i<n;i++){
			printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].p,p[i].ct,p[i].tat,p[i].wt);
		}
		printf("Average Turnaround Time: %.4fms\nAverage Waiting Time: %.4fms\n",avgtat,avgwt);
	}while(1);
	return 0;
}
