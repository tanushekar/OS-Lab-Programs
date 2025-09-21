#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int processID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
    
}Process;

void fcfs(Process [], int );

void main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    
    for(int i=0; i<n; i++)
    {
        printf("Process %d\n", i+1);
        printf("Enter AT: ");
        scanf("%d", &p[i].AT);
        printf("Enter burst time: ");
        scanf("%d", &p[i].BT);
        
        p[i].processID= i+1;
        
        printf("\n");
    }
    
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].AT>p[j+1].AT)
            {
                Process temp= p[j];
                p[j]= p[j+1];
                p[j+1]= temp;
            }
        }
    }
    fcfs(p, n);
}

void fcfs(Process p[], int n)
{
    int elapsedTime=0;
    
    int totalTAT=0;
    int totalWT=0;
    int totalRT=0;
    
    float avgTAT=0;
    float avgWT=0;
    float avgRT=0;
    
    printf("GANTT CHART\n");
    
    for(int i=0; i<n; i++)
    {
        if(p[i].AT > elapsedTime)
         {
            elapsedTime= elapsedTime +(p[i].AT - elapsedTime);
         }
        
        int temp=elapsedTime;
            
        p[i].RT= elapsedTime-p[i].AT;
            
        elapsedTime= elapsedTime+p[i].BT;
            
        p[i].CT= elapsedTime;
        
        p[i].TAT= p[i].CT- p[i].AT;
        p[i].WT= p[i].TAT- p[i].BT;
        
        printf("(%d) P%d (%d)|", temp, p[i].processID, elapsedTime);
        totalTAT += p[i].TAT;
        totalWT += p[i].WT;
        totalRT += p[i].RT;
    }
    printf("\n");
    
    printf("OBSERVATION TABLE\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processID, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }
    
    avgTAT= (float)totalTAT/n;
    avgWT= (float)totalWT/n;
    avgRT= (float)totalRT/n;
    
    printf("The average TAT is %.2f\n", avgTAT);
    printf("The average WT is %.2f\n", avgWT);
    printf("The average RT is %.2f\n", avgRT);
    
}