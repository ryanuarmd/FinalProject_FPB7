#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define ARG_BUFFSIZE 1024
#define MD5_BUFFSIZE 17
#define ARG_LIMIT 32

char * arguments[ARG_LIMIT]; // limit to 32 files only
char * md5sum_files[ARG_LIMIT]; // save the md5 char of files from arguments
static const char base64char[65]={
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
    '='
};


void Init()
{
    int i;
    for(i=0;i<ARG_LIMIT;i++)
    {
        arguments[i] = (char*)malloc(ARG_BUFFSIZE*sizeof(char));
        md5sum_files[i] = (char*)malloc(MD5_BUFFSIZE*sizeof(char));
    }
}

char * md5_main(char * filename)
{
    // open file for read
    int fd = open(filename, O_RDONLY);
    unsigned char buff;
    if(fd == -1) return "\0";

    // main function of MD5
    while(read(fd, buff, sizeof(buff)) >= sizeof(buff))
    {
        printf("tes\n");
        printf("%c",buff);
    }
    printf("\n");
    // close opened file
    close(fd);
    return "ntaps";
}

void md5sum_main(int argc)
{
    int i;
    for(i=0; i<argc; i++)
    {
        strcpy(md5sum_files[i],md5_main(arguments[i]));
    }
}

void OnExit()
{
    int i;
    for(i=0;i<ARG_LIMIT;i++)
    {
        free(arguments[i]);
    }
}

int main(int argc, char *argv[])
{
    Init();
    int i;
    for(i=0;i<argc-1;i++)
    {
        strcpy(arguments[i],argv[i+1]);
    }
    md5sum_main(argc-1);
    for(i=0; i<argc-1; i++)
    {
        printf("%s\n",md5sum_files[i]);
    }
    exit(EXIT_SUCCESS);
}