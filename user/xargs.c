#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define MASSIZE 16

int main(int argc , char *argv[]){

    char buf[MASSIZE];
    read(0, buf,MASSIZE);
    char *xargv[MAXARG];
    int xargc = 0;

    for( int i =1 ; i<argc ;i++){
        //xargv[xargc]=argv[i];
        printf("argv: %c\n", argv[i]);
        xargc++;
        //printf("argc: %d\n", xargc);
    }
    char *p =buf;
    for(int i = 0; i<MASSIZE ; i++){
        if(buf[i] =='\n'){
            int pid = fork();
            if(pid>0){
                p = &buf[i+1];
                wait(0);
            }else{
                buf[i]=0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;

                exec(xargv[0],xargv);
                exit(0);
            }
        }
    }
    wait(0);
    exit(0);




}