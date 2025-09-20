#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>     
 
void *sum(void *);
void *mul(void *);

int sm=0, prod=1;

void *sum(void *parm)
{
    int i, n;
    n= atoi(parm);
    printf("Inside sum thread\n");
    
    for(i=1; i<=n; i++)            
    {
        sm= sm+i;
    }
    printf("Sum thread completed\n");
}

void *mul(void *parm)
{
    int i, n;
    n= atoi(parm);
    printf("Inside mul thread\n");
    
    for(i=2; i<=n; i++)             
    {
        prod= prod*i;
    }
    printf("Mul thread completed\n");
}

void main(int argc, char *argv[])                           
{
    pthread_t T1, T2;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);
    
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);
    
    printf("Inside main thread\n");
    
    printf("SUM= %d\n", sm);
    printf("FACTORIAL= %d\n", prod);
}