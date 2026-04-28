/* 
 * File:   CirBuf.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:29 PM
 */

#include "CirBuf.h"

/* Struct Helper Function */

struct buffer_t* buffer_init(void) {
    struct buffer_t* f = malloc(sizeof(struct buffer_t));
    f->head = 0;
    f->tail = 0;
    return f;
}

int buffer_push(buffer_t *f, uint16_t data) {
    uint16_t next = (f->tail + 1) & BUFFER_MASK;

    if (next == f->head) {
        return 0;   // Buffer Full
    }

    f->buffer[f->tail] = data;
    f->tail = next;
    return 1;       // Buffer Push Success
}

int buffer_force_push(buffer_t *f, uint16_t data) {
    uint16_t next = (f->tail + 1) & BUFFER_MASK;
    
    if (next == f->head) {
        f->head = (f->head + 1) & BUFFER_MASK;   // Buffer Full, Overwrite
    }
    
    f->buffer[f->tail] = data;
    f->tail = next;
    return 1;       // Buffer Push Success
}

int buffer_pop(buffer_t *f) {
    if (f->head == f->tail) {
        return 0;   // Buffer Empty
    }
    
    uint16_t temp = f->buffer[f->head];
    f->head = (f->head + 1) & BUFFER_MASK;
    
    return temp;    // Buffer Pop Success
}

int buffer_is_empty(buffer_t *f) {
    if (f->head == f->tail) {
        return 0;   // Buffer Empty
    }
    
    return 1;       // Buffer Not Empty 
}

double buffer_average(buffer_t *f) {
    uint32_t sum = 0;
    uint16_t count = 0;
    uint16_t current = f->head;
    
    // Traverse from head to tail
    while (current != f->tail) {
        sum += f->buffer[current];
        count++;
        
        // Move to next index with wrap-around
        current = (current + 1) & BUFFER_MASK;
    }

    if (count == 0) {
        return 0; // Avoid division by zero if buffer is empty
    }

    return ((double)sum) / count;
}

/* Struct Helper Function End */