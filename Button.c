/*
 * File:   Button.c
 * Author: ikepr
 *
 * Created on April 9, 2026, 4:00 PM
 */


#include "xc.h"
#include "Button.h"

volatile int isButtonPressed = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) { 
    _T2IF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _IC1Interrupt(void) { // Handles hardware-timed button events and software debouncing
    _IC1IF = 0;
    (void)IC1BUF; // Clear buffer
    isButtonPressed = !PORTBbits.RB6; // 1 if pressed, 0 if released
}

void initButton(void) {
    AD1PCFG = 0xffff; // Set all pins to digital
    TRISBbits.TRISB6 = 1;  // Set RB6 as input
    CNPU2bits.CN24PUE = 1; // Enable pull-up resistor
    
    T2CONbits.TON = 0; // Disable T2
    T2CONbits.TCKPS = 0b11; // Set prescaler to 1:256
    PR2 = 62499; // Set period to 1s
    _T2IF = 0;
    _T2IE = 1; // Enable T2

    __builtin_write_OSCCONL(OSCCON & 0xbf);
    RPINR7bits.IC1R = 6;                    // Assign IC1 to RP6
    __builtin_write_OSCCONL(OSCCON | 0x40);

    IC1CON = 0;              // Reset IC1
    IC1CONbits.ICTMR = 1;    // Set IC1 to use T2
    IC1CONbits.ICI = 0; // Interrupt every capture
    IC1CONbits.ICM = 0b001;  // Capture every edge (rising and falling)
    
    _IC1IF = 0;
    _IC1IE = 1; // Enable IC1
    
    T2CONbits.TON = 1;       // Enable T2
}