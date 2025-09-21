//child.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>


int main(int argc,char *argv[])
{
        int k=2;
        int n1,n2,n3;

        void *ptr;
        int shmid;

        shmid=shmget((key_t)1122, 4096, 0666);
        ptr=shmat(shmid, NULL, 0666);

        printf("CHILD:\n");

        int i=atoi(argv[1]);

        n1=0;
        n2=1;

        sprintf(ptr,"%d",n1);
        ptr+=strlen(ptr);
        printf("%d",n1);

        sprintf(ptr,"%d",n2);
        ptr+=strlen(ptr);
        printf("%d",n2);

        while(k!=i)
        {
                n3=n1+n2;

                sprintf(ptr,"%d",n3);
                ptr+=strlen(ptr);
                printf("%d",n3);

                n1=n2;
                n2=n3;
                k++;
        }
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}