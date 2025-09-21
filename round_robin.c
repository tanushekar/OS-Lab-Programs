#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
	int pid;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;                     
	int flag;                    

}Process;

Process p[15];

void swap(Process *a, Process *b)
{
	Process temp= *a;                       
	*a= *b;
	*b= temp;
}

void sort(int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(p[j].AT > p[j+1].AT)            
			   swap(&p[j], &p[j+1]);             
		}
	}
}

void main()
{
	int n, quantum;
	int tempBT[15];

	int totalWT=0;
    int totalTAT=0;
	
	float avgTAT=0;           
    float avgWT=0;
	
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	
	printf("Enter AT and BT of the processes: \n");
	printf("AT  BT\n");
	
	for(int i=0; i<n; i++)
	{
		printf("Process-%d\n", i+1);
		
		p[i].pid= i+1;
		
		scanf("%d %d", &p[i].AT, &p[i].BT);
		
		tempBT[i]= p[i].BT;
		
		p[i].flag=0;
		
	}
	
	printf("Enter time quantum: ");
	scanf("%d", &quantum);
	
	sort(n);                                
	
	int completed=0;
	
	int curIndex=0;
	int curTime= p[0].AT;
	
	int *waitQueue, front=0, rear=0;
	
	waitQueue=(int *)malloc(n*sizeof(int));
	
	waitQueue[rear]=0;                 
	p[0].flag=1;
	
	while(completed!=n)
	{
		curIndex= waitQueue[front];
		front= (front+1)%n;
		
		if(p[curIndex].BT > quantum)
		{
			p[curIndex].BT -= quantum;
			curTime += quantum;               
			
			printf("|P%d (%d) %d", p[curIndex].pid, quantum, curTime);
		}
		
		else
		{
			curTime = curTime + p[curIndex].BT;        
			printf("|P%d (%d) %d", p[curIndex].pid, p[curIndex].BT, curTime);
			
			p[curIndex].BT=0;                 

			p[curIndex].CT= curTime;
			
			p[curIndex].TAT= p[curIndex].CT- p[curIndex].AT;
			p[curIndex].WT= p[curIndex].TAT- tempBT[p[curIndex].pid-1];              
			
			totalTAT += p[curIndex].TAT;
			totalWT += p[curIndex].WT;
		}
		
		for(int i=0; i<n && p[i].AT<=curTime; i++)      
		{
			if(i==curIndex || p[i].BT==0 || p[i].flag==1)
			  continue;
			
			rear= (rear+1)%n;
			waitQueue[rear]=i;
			p[i].flag=1;	
		}
		
		if(p[curIndex].BT>0)
		{
			rear= (rear+1)%n;
			waitQueue[rear]=curIndex;
		}
		else
		{
			completed++;          
		}

	}
	
	avgTAT= (float)totalTAT/n;
	avgWT= (float)totalWT/n;
	
	printf("OBSERVATION TABLE\n");
	printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
	
	for(int i=0; i<n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT);
	}
	
	printf("Average TAT: %.2f\n", avgTAT);
	printf("Average WT: %.2f\n", avgWT);
}