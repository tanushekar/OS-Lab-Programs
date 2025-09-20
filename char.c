#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 30

int main()
{
    int fd= open("myfile.txt", O_RDWR);              
    int n;
    char buffer[BUFFER_SIZE];
    
    printf("The file desciptor is %d\n", fd);
    
    if(fd==-1)
    {
        printf("Failed to open file\n");
        exit(0);
    }
    
    printf("\nReading first 10 char from file: \n");
    n= read(fd, buffer, 10);
    write(1, buffer, n);
    
    printf("\n\nSkipping 5 char from current position: \n");
    lseek(fd, 5, SEEK_CUR);                                               
    n= read(fd, buffer, 10);
    write(1, buffer, n);
    
    printf("\n\nGoing 10 char before the current position in file: \n");
    lseek(fd, -10, SEEK_CUR);
    n= read(fd, buffer, 10);
    write(1, buffer, n);
    
    printf("\n\nGoing to 5th last char in file: \n");
    lseek(fd, -5, SEEK_END);
    n= read(fd, buffer, 5);
    write(1, buffer, n);
    
    printf("\n\nGoing to 3rd char from the start: \n");
    lseek(fd, 2, SEEK_SET);                                   
    n= read(fd, buffer, 5);        
    write(1, buffer, n);
    
    return 0;
}