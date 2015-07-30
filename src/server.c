#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include "hyper-socket.h"
#include "utils.h"
#include "data.h"

/**
 * Main program
 */
int main(int argc, char** argv) {
    size_t dsize = 10737418240ull;
    Data* data = NULL;
    if (argc < 2 || argc > 3)
    {
        printf("%s:\n\t<infile> [size]\n",argv[0]);
        exit(-1);
    }
    else if (argc == 3)
    {
        dsize = atol(argv[3]);
        fail(dsize,0,"Invalid length to read\n");
        data = bufferBySize(argv[1],dsize);
    }
    else
    {
        data = buffer(argv[1]);
    }
    short port = PORT;
    printf("Establishing connection to: %d\n",port);
    int listen = internet(port,htonl(INADDR_ANY),SERVER);
    int conn = establish(listen);
    double start,end;
    printf("Saving %zu bytes to: %d\n",dsize,port);
    start = now();
    saveToFd(data,conn);
    //write(conn,data->buffer,data->size);
    end = now(); 
    printf("Written %zu bytes in %f seconds or %fB/s\n",data->size,(end-start),data->size/(end-start));
    deallocate(data);
    close(conn);
    close(listen);
}
