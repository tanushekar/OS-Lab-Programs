#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t child_pid, my_pid, parent_pid;
    
    child_pid= fork();
    
    if(child_pid<0)
    {
        printf("Fork failed.Exiting..");
        exit(0);
    }
    
    if(child_pid==0)
    {
        printf("[Child] This is the child process\n");
        my_pid= getpid();
        parent_pid= getppid();
        printf("[Child] My pid is %d\n", my_pid);
        printf("[Child] My parent's pid is %d\n", parent_pid);
        printf("[Child] Exiting..\n");
        exit(0);
    }
    
    else
    {
        printf("[Parent] This is the parent process\n");
        my_pid= getpid();
        parent_pid= getppid();
        printf("[Parent] My pid is %d\n", my_pid);
        printf("[Parent] My parent's pid is %d\n", parent_pid);
        printf("[Parent] Sleeping for 10 seconds\n");
        sleep(10);
        printf("[Parent] Child pid=%d has ended, but it has entry in the process table.It is a zombie process\n", child_pid);
    }
                                 
    return(0);
}