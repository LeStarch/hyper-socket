#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "hyper-socket.h"
#include "utils.h"

//#define TYPE AF_UNIX
#define TYPE AF_INET


/**
 * Opens up an internet socket on geiven port
 * @param port - port number to open
 * @return socket descriptor
 */
int internet(short port,long address,Type type)
{
    //Get socket descriptor
    int sd = socket(TYPE,SOCK_STREAM,0);
    fail(sd,-1,"Failed to allocate socket");
    //Setup an address (port)
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = address;
    addr.sin_port = htons(port);
    //Bind to that address (port)
    if (type == SERVER) {
        int ret = bind(sd,(struct sockaddr*)&addr,sizeof(addr));
        fail(ret,-1,"Failed to bind socket");
    } else if (type == CLIENT) {
        int ret = connect(sd,(struct sockaddr*)&addr,sizeof(addr));
        fail(ret,-1,"Failed to connect to socket");
    }
    return sd;
}
/**
 * Accepts an incoming connection for the given port and returns the connection descriptor.
 * @return connection descriptor
 */
int establish(int sd) {
    int ret = listen(sd,0);
    fail(ret,-1,"Failed to listen on socket");
    return accept(sd,NULL,NULL);
}

