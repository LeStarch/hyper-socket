/*
 * utils.h
 *
 *  Created on: Jul 28, 2015
 *      Author: mstarch
 */

#ifndef HYPER_SOCKET_INCLUDE_UTILS_H_
#define HYPER_SOCKET_INCLUDE_UTILS_H_
    /**
     * Finds minimum of two unsigned long longs
     * @param ull1 - first argument
     * @param ull2 - second argument
     * @return minimum of argument 1 and argument 2
     */
    unsigned long long minll(unsigned long long m1, unsigned long long m2);
    /**
     * Malloc or fail
     * @param size -  size of buffer
     @ @return void* to new buffer
     */
    void* mallocf(size_t size);
    /**
     * Fail if  equivalent
     * @param result - result to check
     * @param check - check value
     */
    void fail(int result, int check, char* message);
    /**
     * Get the current time as a double in seconds since boot
     * @return seconds (double)
     */
    double now();
#endif /* HYPER_SOCKET_INCLUDE_UTILS_H_ */
