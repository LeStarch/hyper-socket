/*
 * hyper-socket.h
 *
 *  Created on: Jul 28, 2015
 *      Author: lestarch
 */

#ifndef HYPER_SOCKET_INCLUDE_HYPER_SOCKET_H_
#define HYPER_SOCKET_INCLUDE_HYPER_SOCKET_H_
    #define PORT 8089
    typedef enum {
        SERVER,
        CLIENT
    } Type;
    /**
     * Opens up an internet socket on geiven port
     * @param port - port number to open
     * @return socket descriptor
     */
    int internet(short port,long address,Type type);
    /**
     * Accepts an incoming connection for the given port and returns the connection descriptor.
     * @return connection descriptor
     */
    int establish(int sd);
#endif /* HYPER_SOCKET_INCLUDE_HYPER_SOCKET_H_ */
