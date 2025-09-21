//CHILD.C

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

#define SIZE 4096

int main(int argc,char *argv[])
{
        int shm_fd=shm_open("VSS",O_CREAT|O_RDWR,0666);                   
        ftruncate(shm_fd,4096);    
        void *ptr=mmap(0,4096,PROT_WRITE,MAP_SHARED,shm_fd,0);            

        int i=atoi(argv[1]);                        
        int j=atoi(argv[2]);
        int flag=0;

        printf("The prime numbers between %d and %d are :",i,j);
        for(int num=i;num<=j;num++)
        {
                flag=0;
                for(int k=2;k<=num/2;k++)
                {
                        if((num%k)==0)
                            flag=1;
                }
                if(flag==0)
                        printf("%d ",num);              
        }
        printf("\n");
}