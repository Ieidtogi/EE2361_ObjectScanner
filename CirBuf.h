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

    /* Buffer Struct */
    typedef struct buffer_t {
        uint16_t buffer[BUFFER_SIZE];
        volatile uint16_t head;
        volatile uint16_t tail;
    } buffer_t;

    /* Function Prototypes */
    struct buffer_t* buffer_init(void);
    int buffer_push(buffer_t *f, uint16_t data);
    int buffer_force_push(buffer_t *f, uint16_t data);
    int buffer_pop(buffer_t *f);
    int buffer_is_empty(buffer_t *f);
    double buffer_average(buffer_t *f);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRBUF_H */

