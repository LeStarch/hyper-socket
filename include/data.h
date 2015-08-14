/*
 * fs-buffer.h
 *
 *  Created on: Jul 28, 2015
 *      Author: lestarch
 */

#ifndef HYPER_SOCKET_INCLUDE_DATA_H_
#define HYPER_SOCKET_INCLUDE_DATA_H_
    #define BLOCK_SIZE 65536ull
    /**
     * Data structure to hold data and metadata
     */
    typedef struct {
        size_t size;
        unsigned char* buffer;
    } Data;

    //Function prototypes
    /**
     * Allocate a data object of given size
     * @param size - size of buffers
     * @return - data object
     */
    Data* allocate(size_t size);
    /**
     * Deallocate data object
     * @param data - data object
     */
    void deallocate(Data* data);
    /**
     * Load the data object from the given file
     * @param data - data object to load
     * @param file - file to read
     */
    void load(Data* data, char* file);
    /**
     * Save the data object to given file
     * @param data - data object to save
     * @param file - file to save to
     */
    void save(Data* data, char* file);
    /**
     * Save the data object to given file
     * @param data - data object to save
     * @param fd - file descriptor to save to
     */
    void saveToFd(Data* data, int fd);
    /**
     * Buffer <size> bytes of the given file in-memory.
     * @param file - path to file to buffer
     * @param size - size to buffer in memory
     * @return Data object
     */
    Data* bufferBySize(char* file,size_t size);
    /**
     * Buffer the full contents of the given file in-memory.
     * @param file - path to file to buffer
     * @return Data object
     */
    Data* buffer(char* file);

#endif /* HYPER_SOCKET_INCLUDE_DATA_H_ */
