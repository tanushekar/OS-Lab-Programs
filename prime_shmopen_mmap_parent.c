//PARENT.C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ipc.h>

#define SIZE 4096

int main(int argc,char *argv[])
{
        int i, j;
        pid_t pid;
        int shm_fd;
        void *ptr;

        if(argc>2)
        {
                sscanf(argv[1],"%d",&i);
                sscanf(argv[2],"%d",&j);
                if(i<2)
                {
                        printf("\n Error input %d\n",i);
                        return 0;
                }
        }
        else
        {
                printf("\n Minimum no of arguments is not passed");
                exit(0);
        }

        pid=fork();

        if(pid==0)
                execlp("./prime","prime",argv[1],argv[2],NULL);            

        else
        {
                wait(NULL);

                shm_fd=shm_open("VSS",O_RDONLY,0666);                   
                ptr=mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);

                printf("%s",(char *)ptr);
                shm_unlink("VSS");
        }
        return 0;
}