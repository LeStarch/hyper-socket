#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>

#include "hyper-socket.h"
#include "utils.h"
#include "data.h"
//Globals for signal handling
double start,end;
Data* data;
int conn = -1,list = -1;
size_t total = 0;

static void catch(int signo) {
    printf("Total %zu bytes in %f seconds or %fB/s\n",total,(end-start),total/(end-start));
    deallocate(data);
    close(conn);
    close(list);
    exit(0);
}

/**
 * Main program
 */
int main(int argc, char** argv) {
    int ret = signal(SIGINT, catch) == SIG_ERR;
    fail(ret,1,"Failed to register signal handler");
    size_t dsize = 10737418240ull;
    if (argc < 3 || argc > 4)
    {
        printf("%s:\n\t<infile> <port> [size]\n",argv[0]);
        exit(-1);
    }
    else if (argc == 4)
    {
        dsize = atol(argv[3]);
        fail(dsize,0,"Invalid length to read\n");
        data = bufferBySize(argv[1],dsize);
    }
    else
    {
        data = buffer(argv[1]);
    }
    short port = (short)atoi(argv[2]);
    list = internet(port,htonl(INADDR_ANY),SERVER);
    printf("Establishing connection to: %d\n",port);
    conn = establish(list);
    start = now();
    total = 0;
    while (1) {
        double new;
        size_t tmp = 0;
        printf("Saving %zu bytes to: %d\n",dsize,port);
        new = now();
        size_t unwritten = data->size;
        while (unwritten > 0)
        {
            sigset_t set,old;
            sigfillset(&set);
            sigprocmask(SIG_BLOCK,&set,&old);
            tmp = write(conn,data->buffer+(data->size - unwritten),minll(BLOCK_SIZE,unwritten));
            if (tmp == -1) {
                end = now();
                break;
            }
            unwritten -= tmp;
            total += tmp;
            end = now();
            sigprocmask(SIG_SETMASK,&old,NULL);
        }
        //saveToFd(data,conn);
        //write(conn,data->buffer,data->size);
        printf("Written %zu bytes in %f seconds or %fB/s\n",(data->size - unwritten),(end-new),data->size/(end-new));
        if (tmp == -1)
            break;
    }
    printf("Total %zu bytes in %f seconds or %fB/s\n",(total),(end-start),data->size/(end-start));
}
