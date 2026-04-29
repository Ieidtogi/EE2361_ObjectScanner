/* 
 * File:   CirBuf.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:29 PM
 */

#include "xc.h"
#include "CirBuf.h"

uint16_t results[8][8];
float nor_results[8][8];

uint16_t max = 0;
uint16_t min;

uint8_t flag = 0;

void data_conversion(buffer_t *f) {
    _SI2C1IE = 0;   // We don't want this to be interrupted by new data input.
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            uint16_t temp = (buffer_pop(f) << 8) | (buffer_pop(f));
            results[i][j] = temp;
        }
    }
    
    data_normalization();
    
    _SI2C1IF = 0;
    _SI2C1IE = 1;
}

void data_normalization(void) {
    _SI2C1IE = 0;   // We don't want this to be interrupted by new data input.
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(!flag) {
                min = results[0][0];
                flag = 1;
            }
            
            uint16_t temp = results[i][j];
                    
            if (temp > max) {
                max = temp;
            } else if (temp < min) {
                min = temp;
            }
        }
    }
    
    if (max == min) {
        return;
    }
    
    float coeff = 1.0f / (max - min);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            nor_results[i][j] = (float)((results[i][j] - min) * coeff);
        }
    }
    
    flag = 0;
    
    _SI2C1IF = 0;
    _SI2C1IE = 1;
}

/* Struct Helper Function */

struct buffer_t* buffer_init(void) {
    struct buffer_t* f = malloc(sizeof(struct buffer_t));
    
    if (f != NULL) {
        f->head = 0;
        f->tail = 0;
    }
    
    return f;
}

int buffer_push(buffer_t *f, uint8_t data) {
    uint16_t next = (f->tail + 1) & BUFFER_MASK;

    if (next == f->head) {
        return 0;   // Buffer Full
    }

    f->buffer[f->tail] = data;
    f->tail = next;
    return 1;       // Buffer Push Success
}

int buffer_force_push(buffer_t *f, uint8_t data) {
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