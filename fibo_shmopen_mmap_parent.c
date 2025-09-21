//parent.c

#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SIZE 4096

int main(int argc,char *argv[])
{
        int i;
        pid_t pid;
        int shm_fd;
        void *ptr;
        
        if(argc>1)
        {
                sscanf(argv[1],"%d",&i);
                if(i<1)
                {
                        printf("\n Error input %d \n",i);
                        return 0;
                }
        }
        else
        {
                printf("Error:Not passing arguments");
                exit(0);
        }

        pid=fork();

        if(pid==0)
        {
                execlp("./fib","fib",argv[1],NULL);
        }
        else if(pid>0)
        {
                wait(NULL);
                printf("\n Parent:Child completed:");

                shm_fd=shm_open("VSS",O_RDONLY,0666);                      
                ptr=mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);             

                printf("Parent printing \n");
                printf("%s",(char *)ptr);
        }
        return 0;
}