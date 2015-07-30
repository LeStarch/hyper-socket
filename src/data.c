#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "utils.h"
#include "data.h"
/**
 * Allocate a data object of given size
 * @param size - size of buffers
 * @return - data object
 */
Data* allocate(size_t size)
{
    printf("Creating data object of size %zu...",size);
    unsigned char* buffer = (unsigned char*)mallocf(size);
    Data* data = (Data*) mallocf(sizeof(Data));
    data->size = size;
    data->buffer = buffer;
    printf("%s","\n");
    return data;
}
/**
 * Deallocate data object
 * @param data - data object
 */
void deallocate(Data* data)
{
    printf("%s\n","Releasing data object");
    free(data->buffer);
    free(data);
}
/**
 * Load the data object from the given file
 * @param data - data object to load
 * @param file - file to read
 */
void load(Data* data, char* file) {
    int fd = open(file,O_RDONLY);
    fail(fd,-1,"Failed to open file for read");
    size_t total = data->size;
    while (total > 0)
    {
         size_t tmp = read(fd,data->buffer+(data->size - total),minll(BLOCK_SIZE,total));
         fail(tmp,-1,"Failed to read file");
         total -= tmp;
    }
    close(fd);
}
/**
 * Save the data object to given file
 * @param data - data object to save
 * @param file - file to save to
 */
void save(Data* data, char* file) {
    int fd = open(file,O_WRONLY|O_CREAT);
    fail(fd,-1,"Failed to open file for write");
    saveToFd(data,fd);
    close(fd);
}
/**
 * Save the data object to given file
 * @param data - data object to save
 * @param fd - file descriptor to save to
 */
void saveToFd(Data* data, int fd) {
    size_t total = data->size;
    while (total > 0)
    {
         size_t tmp = write(fd,data->buffer+(data->size - total),minll(BLOCK_SIZE,total));
         fail(tmp,-1,"Failed to write file");
         total -= tmp;
    }
}
/**
 * Buffer <size> bytes of the given file in-memory.
 * @param file - path to file to buffer
 * @param size - size to buffer in memory
 * @return Data object
 */
Data* bufferBySize(char* file,size_t size) {
    Data* data = allocate(size);
    load(data,file);
    return data;
}
/**
 * Buffer the full contents of the given file in-memory.
 * @param file - path to file to buffer
 * @return Data object
 */
Data* buffer(char* file) {
    struct stat stats;
    int rt = stat(file,&stats);
    fail(rt,-1,"Failed get filesize to buffer");
    if (stats.st_size == 0)
    {
        printf("Cannot buffer full contents of non-file device. Please specify size.\n");
        exit(-1);
    }
    return bufferBySize(file,stats.st_size);
}
