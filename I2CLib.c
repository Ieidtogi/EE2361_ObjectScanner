/* 
 * File:   I2CLib.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:28 PM
 */

#include "xc.h"
#include "I2CLib.h"

volatile I2C_STATE_t i2c_state = I2C_IDLE;
static buffer_t *rx_buffer; 		// Pointer to the circular buffer

volatile unsigned char i2c_addr;
volatile unsigned char *tx_ptr;
volatile uint16_t tx_count;
volatile uint8_t i2c_busy = 0;

void i2c1_init(buffer_t *rxBuf) {
	// I2C Configuration
	I2C1CON = 0;
	I2C1TRN = 0;
	I2C1STAT = 0;
	
	// SDA1/SCL1, RP9/RP8 Use Pull Up Mode
	CNPU2bits.CN21PUE = 1;			// Pull Up Mode RP9
	CNPU2bits.CN22PUE = 1;			// Pull Up Mode RP8

	rx_buffer = rxBuf;
	
	// I2C Start
	i2c1_master_init();
	i2c1_slave_init(SLAVE_ADDRESS);
		
	_MI2C1IF = 0;
	_MI2C1IE = 1; 
	
	I2C1CONbits.I2CEN = 1;
}

void i2c1_master_init(void) {
	I2C1BRG = 0x009D;		// 100 kHz @ Tcy = 16 MHz
}

void i2c1_slave_init(unsigned char address) {
	I2C1ADD = address;
	I2C1MSK = 0;

	_SI2C1IF = 0;
	_SI2C1IE = 1;
}

void i2c1_master_stream_start(unsigned char addr, unsigned char *data, uint16_t length) {
    while(i2c_busy); 			// Ensure previous transfer is done
    
    i2c_addr = addr << 1;
    tx_ptr = data;
    tx_count = length;
    i2c_busy = 1;
    i2c_state = I2C_START;
    
    I2C1CONbits.SEN = 1;		// Trigger Start Condition
}

void i2c1_master_read_trigger(unsigned char addr, unsigned char register_addr) {
    while(i2c_busy);			// Ensure previous transfer is done
    
    i2c_addr = addr << 1 | 1;	// Shift for R/nW bit (1)
    tx_ptr = &register_addr;	// Point to the single trigger byte
    tx_count = 1;
    i2c_busy = 1;
    i2c_state = I2C_START;
    
    I2C1CONbits.SEN = 1;		// Trigger Start Condition

/**
 * Master I2C1 Interrupt Service Routine
 */

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
	switch (i2c_state) {
		case I2C_START:
			i2c_state = I2C_SEND_ADDR;
			I2C1TRN = i2c_addr;
			break;

		case I2C_SEND_ADDR:
		case I2C_SEND_DATA:
			if (tx_count > 0) {
                i2c_state = I2C_SEND_DATA;
				I2C1TRN = *tx_ptr;				// Send the data or trigger
                if (tx_count > 1) tx_ptr++; 	// Send next byte in stream if exists.
                tx_count--;
            } else {
                i2c_state = I2C_STOP;
                I2C1CONbits.PEN = 1;
            }
            break;

		case I2C_STOP:
			i2c_state = I2C_IDLE;
			i2c_busy = 0;
			break;
			
		default:
			i2c_state = I2C_IDLE;
			i2c_busy = 0;
			break;
	}

	_MI2C1IF = 0;							// Clear interrupt flag
}

/**
 * Slave I2C1 Interrupt Service Routine
 */

void __attribute__((interrupt, auto_psv)) _SI2C1Interrupt(void) {
    uint16_t temp;
    if (I2C1STATbits.D_A == 1) {					// Data byte received
        temp = I2C1RCV;
        if (rx_buffer_ptr != NULL) {
            BUFFER_ForcePush(rx_buffer_ptr, temp);	// Store in circular buffer
        }
    } else {
        temp = I2C1RCV;								// Dummy read for address match
    }
	
    _SI2C1IF = 0;
}

