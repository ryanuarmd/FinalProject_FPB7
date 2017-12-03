#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "stdio.h"



int main(int argc, char *argv[])
{
  int fsrc, fdes;

  if(argc != 3){
    printf("Coba: cp [Sourcenya] [Destinasinya]\n");
    exit();
  }

  if(fsrc=open(argv[1],0_RDONLY) < 0){
    printf("Cek lagi File Sourcenya\n");
    exit();
  }

  if(fdes=open(argv[2],) < 0){

    
  }

  
  exit();
}
