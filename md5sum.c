#include "CustomMD5Header.h"

void md5string(md5context_t * ctx, char * input);

int main(int argc, char **argv){
    if(argc < 2 || strcmp(argv[1],"-s")!=0 || strcmp(argv[1],"-f")==0){
        printf(1,"Usage:\n");
        printf(1,"-s: digest string\n");
        printf(1,"-f: digest file\n");
        exit();
    }
    md5context_t ctx;
    if(strcmp(argv[1],"-s")==0){
        md5string(&ctx,argv[2]);
    }
    else if(strcmp(argv[1],"-f")==0){

    }
    return 0;
}

void md5string(md5context_t * ctx, char * input){
    uint32 len = strlen(input);
    byte result[16];
    Init_Context(ctx);
    Update_Context(ctx, (byte*)input, len);
    Finalization(ctx,result);
    int i;
    for(i=0; i<16; i++)
        printf(1,"%2.2x",result[i]);
    printf(1,"\n");
}
