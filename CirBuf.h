/* 
 * File:   CirBuf.h
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:28 PM
 */

#include <stdint.h>

#ifndef CIRBUF_H
#define	CIRBUF_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Must be the power of 2
    #define BUFFER_SIZE 128
    #define BUFFER_MASK (BUFFER_SIZE - 1)

    /* Buffer Struct */
    typedef struct {
        uint16_t buffer[BUFFER_SIZE];
        volatile uint16_t head;
        volatile uint16_t tail;
    } BUFFER_t;

    /* Function Prototypes */
    void BUFFER_Init(BUFFER_t *f);
    int BUFFER_Push(BUFFER_t *f, uint16_t data);
    int BUFFER_ForcePush(BUFFER_t *f, uint16_t data);
    int BUFFER_Pop(BUFFER_t *f);
    int BUFFER_IsEmpty(BUFFER_t *f);
    double BUFFER_Average(BUFFER_t *f);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRBUF_H */

