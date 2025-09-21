#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int pid, AT, BT, CT, TAT, WT, priority;          
}Process;                                                
                                                         
Process p[15];

void main()
{
    int n, tempBT[15];                               
    int totalTAT=0, totalWT=0;
    float avgTAT=0, avgWT=0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the AT, BT AND Priority\n");
    printf("AT BT Priority\n");

    for(int i=0; i<n; i++)
    {
        printf("Enter the AT, BT AND Priority for P-%d\n", i+1);
        printf("AT BT Priority\n");
        
        p[i].pid=i+1;
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].priority);

        tempBT[i]= p[i].BT;                  
    }

    printf("GANTT CHART\n");

    int minIndex, minPriority;
    int curTime=0, completed=0;

  while(completed!=n)
  {
    minIndex=-1;
    minPriority=9999;

    for(int i=0; i<n; i++)
    {
        if(p[i].AT<=curTime && p[i].BT>0)                          
        {
            if(p[i].priority<minPriority || (p[i].priority==minPriority && p[i].AT<p[minIndex].AT))
            {
                minIndex= i;
                minPriority=p[i].priority;
            }
        }
    }

    curTime++;                               

    if(minIndex != -1)
    {
        p[minIndex].BT--;

        printf("|P%d(1)%d ", p[minIndex].pid, curTime);

        if(p[minIndex].BT==0)
        {
            p[minIndex].CT= curTime;
            p[minIndex].TAT= p[minIndex].CT-p[minIndex].AT;
            p[minIndex].WT= p[minIndex].TAT- tempBT[minIndex];     

            totalTAT+= p[minIndex].TAT;
            totalWT+= p[minIndex].WT;

            completed++;                       
        }
     }
  }

  avgTAT=(float)totalTAT/n;
  avgWT= (float)totalWT/n;

  printf("Observation table\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

  for(int i=0; i<n; i++)                        
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, tempBT[i], p[i].priority, p[i].CT, p[i].TAT, p[i].WT);
  }

  printf("AVG TAT=%.2f\n", avgTAT);
  printf("AVG WT=%.2f\n", avgWT);
}