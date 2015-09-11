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

#include "hyper-socket.h"
#include "utils.h"
#include "data.h"

/**
 * Main program
 */
int main(int argc, char** argv) {
    if (argc != 3 )
    {
        printf("%s:\n\t<host>\n",argv[0]);
        exit(-1);
    }
    short port = (short)atoi(argv[2]);
    char buffer[BLOCK_SIZE];
    printf("Establishing connection to: %d\n",port);
    int conn = internet(port,inet_addr(argv[1]),CLIENT);
    double start,end;
    printf("Reading data from: %s:%d\n",argv[1],port);
    size_t total = 0;
    int ret = 0;
    start = now();
    while (0 < (ret = read(conn,buffer,BLOCK_SIZE))) {
        total += ret;
    }
    end = now();
    printf("Read %zu bytes in %f seconds or %fB/s\n",total,(end-start),total/(end-start));
    close(conn);
}
