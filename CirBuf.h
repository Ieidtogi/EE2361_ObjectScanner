/* 
 * File:   CirBuf.h
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:28 PM
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef CIRBUF_H
#define	CIRBUF_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Must be the power of 2
    #define BUFFER_SIZE 128
    #define BUFFER_MASK (BUFFER_SIZE - 1)

    extern uint16_t results[8][8];
    extern float nor_results[8][8];

    /* Buffer Struct */
    typedef struct buffer_t {
        uint8_t buffer[BUFFER_SIZE];
        volatile uint8_t head;
        volatile uint8_t tail;
    } buffer_t;

    /* Function Prototypes */
    
    /**
     * Data Conversion Function: Converts raw data from the buffer into 16-bit values and stores them in the results array.
     * It also calls the data normalization function to normalize the results.
     */

    void data_conversion(buffer_t *f);

    /**
    * Data Normalization Function: Normalizes the 16-bit values in the results array to a range of 0.0 to 1.0 and stores them in the nor_results array.
    * It calculates the minimum and maximum values in the results array to perform normalization.
    */

    void data_normalization(void);
    
    /**
     * Buffer Initialization Function: Allocates memory for a new buffer and initializes its head and tail indices.
     * Returns a pointer to the newly created buffer, or NULL if memory allocation fails.
     */

    struct buffer_t* buffer_init(void);

    /**
     * Buffer Push Function: Adds a byte of data to the buffer. If the buffer is full, it returns 0 to indicate failure; otherwise, it returns 1 for success.
     */

    int buffer_push(buffer_t *f, uint8_t data);

    /**
     * Buffer Force Push Function: Adds a byte of data to the buffer. If the buffer is full, it overwrites the oldest data and returns 1 for success.
     */

    int buffer_force_push(buffer_t *f, uint8_t data);

    /**
     * Buffer Pop Function: Removes a byte of data from the buffer. If the buffer is empty, it returns 0 to indicate failure; otherwise, it returns 1 for success.
     */

    int buffer_pop(buffer_t *f);

    /**
     * Buffer Is Empty Function: Checks if the buffer is empty. Returns 1 if the buffer is empty, and 0 if it contains data.
     */

    int buffer_is_empty(buffer_t *f);

    /**
     * Buffer Average Function: Calculates the average of the data currently stored in the buffer. It sums all the values from head to tail and divides by the count of values to return the average as a double.
     */

    double buffer_average(buffer_t *f);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRBUF_H */

