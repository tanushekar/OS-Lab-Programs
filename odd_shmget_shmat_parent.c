//PARENT.C

#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<unistd.h>

typedef struct
{
        int n;
        int arr[100];
}pack_t;

int main()                            
{
        int shmid=shmget((key_t)1234, sizeof(pack_t), 0666|IPC_CREAT);
        pack_t* ptr=(pack_t*)shmat(shmid, NULL, 0666);

        printf("[PARENT]Enter n:");
        scanf("%d",&ptr->n);

        pid_t child_pid;

        child_pid=fork();

        if((child_pid==0))
                execlp("./odd","odd",NULL);
        else
        {
                wait(NULL);
                printf("[PARENT] Child finished executing");
                printf("[PARENT]the first %d odd numbers are:\n",ptr->n);
                for(int i=0; i<ptr->n; i++)
                        printf("%d",ptr->arr[i]);
                printf("\n");
        }
        shmdt((void*)ptr);
        shmctl(shmid, IPC_RMID, NULL);
        return 0;
}