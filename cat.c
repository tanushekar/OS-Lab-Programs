#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])                        
{
    FILE *fp;
    char ch;
    
    if(argc<2)
    {
        printf("File name not entered\n");
        exit(1);
    }
    
    fp= fopen(argv[1], "r");
    
    if(fp==NULL)
    {
        printf("file doesn't exist\n");
        exit(1);
    }
    
    while( (ch=fgetc(fp)) !=EOF)                
    {
        printf("%c", ch);
    }
    
    fclose(fp);
    printf("\n");

    return 0;
}
