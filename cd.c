#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#define ARG_BUFFSIZE 1024
#define stdout 1
/*
cd by itself or cd ~ will always put you in your home directory.

cd . will leave you in the same directory you are currently in 
    (i.e. your current directory won't change). This can be useful if your shell's 
    internal code can't deal with the directory you are in being recreated; 
    running cd . will place your shell in the recreated directory.

cd dir (without a /) will put you in a subdirectory; 
    for example, if you are in /usr, typing cd bin will put you in /usr/bin, 
    while cd /bin puts you in /bin.

cd .. will move you up one directory. So, if you are /usr/bin/tmp, 
    cd .. moves you to /usr/bin, while cd ../.. moves you to /usr (i.e. up two levels). 
    You can use this indirection to access subdirectories too. 
    So, from /usr/bin/tmp, you can use cd ../../local to go to /usr/local.
*/
char * arguments; 

void init()
{
    arguments = (char *)malloc(ARG_BUFFSIZE);
}

void onProgram_exit()
{
    free(arguments);
}

void cd_main(char * path)
{
    int fd;
    fd = chdir(path);
    if(fd < 0){
     //   printf(stdout, "Error opening directory\n");
        onProgram_exit();
        exit(EXIT_FAILURE);
    }
    onProgram_exit();
}

int main(int argc, char **argv)
{
    // get arguments, cd only have 1 argument valid
    arguments = argv[1];
    if(argc == 1){
        arguments = "..";
        cd_main(arguments);
    }
    cd_main(arguments);
    exit(EXIT_SUCCESS);
}

