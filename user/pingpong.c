#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WD 1

int main(int argc , char const *argv){
    char buf = 'P';
    int fd_c2p[2];
    int fd_p2c[2];  //父对子
    pipe(fd_c2p);
    pipe(fd_p2c);

    int pid=fork();
    int exit_status = 0; //??

    if(pid < 0){
        fprintf(2,"fork() error!\n");
        close(fd_c2p[RD]);
        close(fd_p2c[WD]);
        close(fd_c2p[WD]);
        close(fd_p2c[RD]);
        exit(1);

    }else if(pid == 0){ //子进程  子进程写
        close(fd_p2c[WD]);
        close(fd_c2p[RD]);
        if(read(fd_p2c[RD],&buf,sizeof(char)) != sizeof(char) ){
            fprintf(2 , "child read() error\n");
            exit_status = 1;
        }else{
            fprintf(1 , "%d: received ping\n" , getpid());
        }
        if(write(fd_c2p[WD],&buf,sizeof(char))!=sizeof(char)){
            fprintf(2 , "child write() error\n");
            exit_status = 1;
        }
        close(fd_p2c[RD]);
        close(fd_c2p[WD]);

        exit(exit_status);

    }else{
        close(fd_p2c[RD]);//父进程写
        close(fd_c2p[WD]);
        if(write(fd_p2c[WD],&buf,sizeof(char))!=sizeof(char)){
            fprintf(2 , "parent write() error\n");
            exit_status = 1;
        }
        if(read(fd_c2p[RD],&buf,sizeof(char)) != sizeof(char) ){
            fprintf(2 , "parent read() error\n");
            exit_status = 1;
        }else{
            fprintf(1 , "%d: received pong\n" , getpid());
        }

        close(fd_p2c[WD]);
        close(fd_c2p[RD]);

        exit(exit_status);


    }


}