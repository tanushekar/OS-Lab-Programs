#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>                  
#include<sys/types.h>

int main()
{
    pid_t child_pid, parent_pid, my_pid;

    child_pid= fork();
    
    if(child_pid<0)
    {
        printf("Fork failed. Exiting..\n");
        exit(0);
    }
    
    if(child_pid==0)
    {
        printf("[Child] This is the child process\n");
        my_pid= getpid();
        parent_pid= getppid();
        printf("[Child] My pid is %d\n", my_pid);
        printf("[Child] My parent's pid is %d\n", parent_pid);
        printf("[Child] Sleeping for 10 seconds\n");
        sleep(10);
        
        printf("[Child] My parent ended so I am an orphan process adopted by init process\n");
    }
    
    else
    {
        printf("[Parent] This is the parent process\n");
        my_pid= getpid();
        parent_pid= getppid();
        printf("[Parent] My pid is %d\n", my_pid);
        printf("[Parent] My parent's pid is %d\n", parent_pid);
        printf("[Parent] Exiting..\n");
        exit(0);                                        
    }
    
    return 0;
}