//CHILD.C

#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/types.h>

typedef struct{
        int n;
        int arr[100];
}pack_t;

int main()
{
        int shmid=shmget((key_t)1234,sizeof(pack_t),0666);      
                                                                
        pack_t * ptr=(pack_t *)shmat(shmid,NULL,0666);          

        for(int i=0; i<ptr->n; i++)
                ptr->arr[i]=2*i+1;
                
        shmdt((void*)ptr);
        return 0;
}