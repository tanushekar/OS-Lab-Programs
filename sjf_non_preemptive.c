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
    int finished;       
     
}Process;

void sjfNP(Process [], int );

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
        printf("Enter BT: ");
        scanf("%d", &p[i].BT);

        p[i].finished=0;                   
        p[i].processID=i+1;               
        printf("\n"); 
    }
    sjfNP(p, n);
}

void sjfNP(Process p[], int n)
{
    int totalTAT=0;
    int totalWT=0;
    int totalRT=0;

    float avgTAT=0;
    float avgWT=0;
    float avgRT=0;

    int elapsedTime=0;
    int remainingProcesses=n;
  
    printf("GANTT CHART\n");

    while(remainingProcesses)                           
    {
        int exec=-1;
        int shortestBT=9999;

        for(int i=0; i<n; i++)
        {
          if(!p[i].finished && p[i].AT<=elapsedTime)
          {
            if(p[i].BT<shortestBT)
            {
                exec=i;
                shortestBT= p[i].BT;                
            }
          }
        }

        if(exec== -1)
        {
          printf("(%d)***(%d)|", elapsedTime, elapsedTime+1);
          elapsedTime++;
        }

       else
       {
          int temp= elapsedTime;

          p[exec].RT= elapsedTime-p[exec].AT;

          elapsedTime += p[exec].BT;

          p[exec].finished=1;

          remainingProcesses--;

          p[exec].CT= elapsedTime;

          p[exec].TAT= p[exec].CT- p[exec].AT;
          p[exec].WT= p[exec].TAT- p[exec].BT;
        
          printf("(%d)P%d(%d)|", temp, p[exec].processID, elapsedTime);
       }
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0; i<n; i++)
    {
       printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processID, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);

       totalTAT += p[i].TAT;
       totalWT += p[i].WT;
       totalRT += p[i].RT;
    }

    avgTAT= (float)totalTAT/n;
    avgWT= (float)totalWT/n;
    avgRT= (float)totalRT/n;

    printf("The average TAT is %.2f\n", avgTAT);     
    printf("The average WT is %.2f\n", avgWT);
    printf("The average RT is %.2f\n", avgRT);
}