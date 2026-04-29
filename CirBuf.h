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
    
    void data_conversion(buffer_t *f);
    void data_normalization(void);
    
    struct buffer_t* buffer_init(void);
    int buffer_push(buffer_t *f, uint8_t data);
    int buffer_force_push(buffer_t *f, uint8_t data);
    int buffer_pop(buffer_t *f);
    int buffer_is_empty(buffer_t *f);
    double buffer_average(buffer_t *f);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRBUF_H */

