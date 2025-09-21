#include<stdio.h>
typedef struct process
{
    int pid;
    int AT;
    int BT;
    int CT;
    int WT;
    int TAT;
    int RT;
    int remainingTime;                     
}Process;

void sjfPreemptive(Process[], int);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    for(int i=0; i<n; i++)
    {
        printf("Process %d\n", i+1);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].AT);
        printf("Enter burst time: ");
        scanf("%d", &p[i].BT);
        
        p[i].pid= i+1;
        p[i].remainingTime= p[i].BT;
        printf("\n");
    }
    
    sjfPreemptive(p, n);
    return 0;
}

void sjfPreemptive(Process p[], int n)
{
    int timeProgress[100], processTrack[100];                                                                                     
    int j=-1, k=-1;
    
    float avgWT=0;
    float avgTAT=0;
    float avgRT=0;
    
    int totalWT=0;
    int totalRT=0;
    int totalTAT=0;
    
    int elapsedTime=0;
    int remainingProcesses=n;
    
    timeProgress[++j]=0;
    
    while(remainingProcesses)
    {
        int exec=-1;
        int shortestBT=9999;
        
        for(int i=0; i<n; i++)
        {
            if(p[i].AT<= elapsedTime && p[i].remainingTime>0)
            {
                if(p[i].remainingTime < shortestBT)           
                {
                    shortestBT= p[i].remainingTime;         
                    exec=i;
                }
            }
        }
        
        if(exec==-1)         
        {
            processTrack[++k]=0;
            elapsedTime++;
            timeProgress[++j]= elapsedTime;
            continue;                            
        }
        
        if(p[exec].remainingTime== p[exec].BT)      
        {
            p[exec].RT= elapsedTime- p[exec].AT;    
        }
        
        p[exec].remainingTime--;
        elapsedTime++;
        
        processTrack[++k]= p[exec].pid;
        timeProgress[++j]= elapsedTime;
        
        if(p[exec].remainingTime==0)
        {
            p[exec].CT= elapsedTime;
            p[exec].TAT= p[exec].CT- p[exec].AT;
            p[exec].WT= p[exec].TAT- p[exec].BT;
            
            totalTAT += p[exec].TAT;
            totalRT += p[exec].RT;
            totalWT += p[exec].WT;
            
            remainingProcesses--;             
        }
    }

    avgRT =(float)totalRT/n;
    avgTAT= (float)totalTAT/n;
    avgWT= (float)totalWT/n;
    
    printf("Observation table\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT,p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }
    
    printf("GANTT CHART\n");
    
    for(int i=0; i<=k ;i++)
      printf("|P%d  ", processTrack[i]);
    printf("\n");
    
    for(int i=0; i<=j; i++)
      printf("%d  ", timeProgress[i]);
    printf("\n");
    
    printf("AVG WAITING TIME:%.2f\n", avgWT);                
    printf("AVG TURN AROUND TIME:%.2f\n", avgTAT);
    printf("AVG RESPONSE TIME:%.2f\n", avgRT);
}