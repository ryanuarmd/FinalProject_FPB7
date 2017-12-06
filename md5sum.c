#include "CustomMD5Header.h"
#include "printf.c"

int main(int argc, char **argv){
    if(argc < 2){
        printf(1,"Usage:\n");
        printf(1,"-s: digest string\n");
        printf(1,"-f: digest file\n");
        exit();
    }
    md5context_t ctx;
    if(strcmp(argv[1],"-s")==0){

    }
    else if(strcmp(argv[1],"-f")==0){
        
    }
    return 0;
}