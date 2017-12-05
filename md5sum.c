//#include "types.h"
//#include "stat.h"
//#include "user.h"
//#include "defs.h"
//#include "fs.h"
//#include "kbd.h"
#include "string.c"
//#include "printf.c"
#include <stdio.h>

#define ARG_BUFFSIZE 1024
#define MD5_BUFFSIZE 17
#define byte unsigned char
#define uint32 unsigned int
#define LROT(integer, n_shift) ((integer << n_shift) | (x >> (32-n_shift)))
#define F(x,y,z) ((x & y) | ((~x) & z))
#define G(x,y,z) ((x & z) | (y & (~z)))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | (~z)))

static const char base64char[65]={
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
    '='
};

uint32 hash1, hash2, hash3, hash4;
uint32 Kmap[64] =   // floor(abs(sin(i+1))) * pow(2,32); i=0...63
{
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void md5sum_main(byte * inputmsg, unsigned long inputmsglen)
{
    byte * newmsg = NULL;
    unsigned long newlength = inputmsglen+1;
    printf("%c\n",inputmsg);
    uint32 rotate[]=
    {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9 ,14, 20, 5, 9 ,14, 20, 5, 9 ,14, 20, 5, 9 ,14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
// 1st - Append Padding Bits
    // the new length of inputmsg after padding
    while(newlength%512 != 448) newlength++;
    newlength /= 8; // length in byte

    newmsg = calloc(newlength + 64, 1); // allocate and zeroize with unit of byte, 1 -> 1 byte
    memcpy(newmsg, inputmsg, inputmsglen); // copy inputmsglen bytes from inputmsg into newmsg
    newmsg[inputmsglen] = 0x80; // in byte unit, 10000000
// 2nd - Append Length
    uint32 bitslen = 8*inputmsglen;
    memcpy(newmsg+newlength, &bitslen, 8);
}

int main(int argc, char **argv)
{
    if(argc < 2){
        printf("Invalid use of md5sum command\n");
    }
    md5sum_main(argv[1], strlen(argv[1]));   
    return 0;
}