//#include "umalloc.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned char byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef struct {
    uint32 state[4];    // wordA, wordB, wordC, wordD
    uint64 count;    // 64 - bit word
    byte buffer[64];    // input buffer
}md5context_t;

#define WORD_A 0x67452301
#define WORD_B 0xefcdab89
#define WORD_C 0x98badcfe
#define WORD_D 0x10325476

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

uint32 rotate[]=
{
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9 ,14, 20, 5, 9 ,14, 20, 5, 9 ,14, 20, 5, 9 ,14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

#define F(x,y,z) ((x & y) | ((~x) & z))
#define G(x,y,z) ((x & z) | (y & (~z)))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | (~z)))
#define LROT(integer, n_shift) ((integer << n_shift) | (x >> (32-n_shift)))

#define FF(A,B,C,D,x,s,t){ \
    A += F(B, C, D,) + x + (uint32)(t); \
    A = LROT(A, s); \
    A += B; \
}

#define GG(A,B,C,D,x,s,t){ \
    A += G(B, C, D) + x + (uint32)(t); \
    A  = LROT(A, s); \
    A += B; \
}

#define HH(A,B,C,D,x,s,t){ \
    A += H(B, C, D,) + x + (uint32)(t); \
    A = LROT(A, s); \
    A += B; \
}

#define II(A,B,C,D,x,s,t){ \
    A += I(B, C, D) + x + (uint32)(t); \
    A  = LROT(A, s); \
    A += B; \
}

void Init_Context(md5context_t * ctx){
    ctx->count = 0;
    ctx->state[0] = (uint32)WORD_A;
    ctx->state[1] = (uint32)WORD_B;
    ctx->state[2] = (uint32)WORD_C;
    ctx->state[3] = (uint32)WORD_D;
}

void Transform(md5context_t * ctx, byte * msg, uint64 len){
    uint32 XX[4] = {
        ctx->state[0], ctx->state[1], ctx->state[2], ctx->state[3]
    };
    uint32 X[16];
}

void Update_Context(md5context_t * ctx, byte * input, uint64 len){
    uint64 newlength = len + (64-len%64);
    byte * input_pad = (byte *)malloc(newlength);
    memcpy(input_pad,input,len);
    uint32 i;
    for(i=len+1; i<newlength; i++) input_pad[i] = (byte)0x0;
    input_pad[len] = (byte)0x80;
    memcpy(input_pad+newlength-8,&len, 8);
    Transform(ctx, input_pad, newlength);
}