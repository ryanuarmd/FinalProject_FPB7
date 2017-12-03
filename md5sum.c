//#include "types.h"
//#include "stat.h"
//#include "user.h"
#include "fs.h"
#include "kbd.h"
#include "string.c"
//#include "printf.c"
#include <stdio.h>

#define ARG_BUFFSIZE 1024
#define MD5_BUFFSIZE 17
#define byte unsigned char
#define uint32 unsigned int
#define LROT(integer, n_shift) ((integer << n_shift) | (x >> (32-n_shift)))

static const char base64char[65]={
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
    '='
};

uint32 hash1, hash2, hash3, hash4;

void md5sum_main(char * msg)
{
    unsigned long msglen = strlen(msg);
    
}

int main(int argc, char **argv)
{
    // printint(1,t,10,1);
    // printf(1,"\n");
    if(argc < 2){
        printf("Invalid use of md5sum command\n");
    }
    md5sum_main(argv[1]);   
    return 0;
}