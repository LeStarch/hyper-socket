#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>

#include "utils.h"
/**
 * Finds minimum of two unsigned long longs
 * @param ull1 - first argument
 * @param ull2 - second argument
 * @return minimum of argument 1 and argument 2
 */
unsigned long long minll(unsigned long long m1, unsigned long long m2)
{
    return (m1 > m2)? m2: m1;
}
/**
 * Malloc or fail
 * @param size -  size of buffer
 @ @return void* to new buffer
 */
void* mallocf(size_t size)
{
    void* buff = NULL;
    int try = 3;
    printf("%s","allocating");
    while (NULL == (buff = (void*)malloc(size)))
    {
        if (try-- <= 0)
        {
            printf("%s"," failed");
            exit(-1);
        }
        printf("%s"," retry...");
    }
    printf("%s"," done");
    return buff;
}
/**
 * Fail if  equivalent
 * @param result - result to check
 * @param check - check value
 */
void fail(int result, int check, char* message)
{
    if (result != check)
        return;
    printf("%s with error %s\n",message,strerror(errno));
    exit(-1);
}
/**
 * Get the current time as a double in seconds since boot
 * @return seconds (double)
 */
double now()
{
    struct timeval tv;
    if (gettimeofday(&tv,NULL) != 0)
        return -1.0;
    double stamp = (double)tv.tv_sec;
    stamp += ((double)tv.tv_usec)/1000000.0;
    return stamp;
}
