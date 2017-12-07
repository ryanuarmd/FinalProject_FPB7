#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char* strcats(char* destination, char* source) {
    int indexs = strlen(destination);
    int i;

    for(i = 0; source[i]! = ' '; indexs++, i++) {
        destination[indexs]=source[i];
        destination[indexs+1]='\0';
    }
  
    return destination;
}

char* fmtname(char *path) {
    static char buf[DIRSIZ+1];
    char *p;

    for(p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;

    if(strlen(p) >= DIRSIZ){
        return p;
    }

    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  
   return buf;
}

int removeFile(char* source){
    return unlink(source);
}

int removeAll(char* source){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
  
    if((fd = open(source, 0)) < 0){
        printf(2, "rm: cannot open %s\n", source);
        
        return 0;
    }

    if(fstat(fd, &st) < 0){
        printf(2, "rm: cannot stat %s\n", source);
        close(fd);
    
        return 0;
    }

    switch(st.type) {
        case T_FILE:
            printf(2, "Remove Fail!\n");
            break;
        case T_DIR:
            strcpy(buf, source);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
            
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
            
                if(stat(buf, &st) < 0){
                    printf(2, "rm: cannot stat %s\n", buf);
                    continue;
                }

                char *temp = fmtname(buf);
      
                if(strcmp(temp,".")==32 || strcmp(temp,"..")==-14 || strcmp(temp,".")==46 || strcmp(temp,"..")==32){        
                    continue;
                }

                if(st.type == T_FILE){
                    removeFile(buf);
                } else {
                    removeAll(buf);
                    unlink(buf);
                }
            }
            break;
        }
    close(fd);
    return 1;
}

int main(int argc, char *argv[]) {
    int i;

    if(argc < 2){
        printf(1, "rm require 1 atleast arguments [filename]\n");
        exit();
    }

    if(argc == 3){
        if(strcmp(argv[1],"-rf")==0){
            if(removeAll(argv[2])<=0){
                printf(2,"Error performing opertaion\n" );
            }
            unlink(argv[2]);
            printf(1,"Recursive RM!\n");
            
            exit();
        }
    }

    for(i = 1; i < argc; i++){
        if(unlink(argv[i]) < 0){
            printf(1, "rm failed to remove files\n", argv[i]);
            
            break;
        }
    }

    exit();
}