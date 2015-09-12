/*
 * client.c
 *
 *  Created on: Jul 29, 2015
 *      Author: lestarch
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#include "hyper-socket.h"
#include "utils.h"
#include "data.h"

//Globals for signal handling
double start,end;
int conn = -1;
size_t total = 0;

static void catch(int signo) {
    printf("Total %zu bytes in %f seconds or %fB/s\n",total,(end-start),total/(end-start));
    close(conn);
    exit(0);
}

/**
 * Main program
 */
int main(int argc, char** argv) {
    int r = signal(SIGINT, catch) == SIG_ERR;
    fail(r,1,"Failed to register signal handler");
    if (argc != 3 )
    {
        printf("%s:\n\t<host>\n",argv[0]);
        exit(-1);
    }
    short port = (short)atoi(argv[2]);
    char buffer[BLOCK_SIZE];
    printf("Establishing connection to: %d\n",port);
    conn = internet(port,inet_addr(argv[1]),CLIENT);
    printf("Reading data from: %s:%d\n",argv[1],port);
    int ret = 1;
    start = now();

    while (0 < ret) {
        sigset_t set,old;
        sigfillset(&set);
        sigprocmask(SIG_BLOCK,&set,&old);
        ret = read(conn,buffer,BLOCK_SIZE);
        total += ret;
        end = now();
        sigprocmask(SIG_SETMASK,&old,NULL);
    }

    printf("Read %zu bytes in %f seconds or %fB/s\n",total,(end-start),total/(end-start));
    close(conn);
}
