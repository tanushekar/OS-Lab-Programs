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
    int isCompl;
    int priority;        

}Process;

Process p[15];

void main()
{
    int n;
    int totalTAT=0, totalWT=0;
    float avgTAT=0, avgWT=0;
    
    int idleTime=0;                   
    int minPriority, minIndex;
    int curTime=0, completed=0;      
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter AT, BT and PRIORITY: ");
    printf("\nAT BT Priority\n");
    
    for(int i=0; i<n; i++)
    {
        printf("Process-%d\n", i+1);
        p[i].pid= i+1;
        
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].priority);
        
        p[i].isCompl=0;           
    }
    
    printf("GANTT CHART\n");
    
    while(completed != n)           
    {
        minIndex= -1;
        minPriority= 9999;
        
        for(int i=0; i<n; i++)             
        {
            if(p[i].AT <= curTime && p[i].isCompl==0)
            {
                if(p[i].priority < minPriority || (p[i].priority==minPriority && p[i].AT < p[minIndex].AT) )
                {
                    minPriority= p[i].priority;
                    minIndex=i;
                }
            }
        }
        
        if(minIndex==-1)          
        {
            curTime++;
            idleTime++;          
        }
        
        else
        {
            if(idleTime>0)
            {
                printf("|Idle time until %d", idleTime);
            }
            idleTime=0;                    
            
            curTime+= p[minIndex].BT;
            
            p[minIndex].CT= curTime;
            p[minIndex].TAT= p[minIndex].CT- p[minIndex].AT;
            p[minIndex].WT= p[minIndex].TAT- p[minIndex].BT;
            
            totalTAT+=p[minIndex].TAT;
            totalWT+=p[minIndex].WT;
            
            p[minIndex].isCompl=1;
            
            completed++;                     
            
            printf("|P%d (%d) %d", p[minIndex].pid, p[minIndex].BT, p[minIndex].CT);      
        }
    }
    
    printf("\n");
    avgTAT= (float)totalTAT/n;
    avgWT= (float)totalWT/n;
    
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
    
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].priority);
    }
    
    printf("AVERAGE TAT is %.2f\n", avgTAT);
    printf("AVERAGE WT is %.2f\n", avgWT);
}