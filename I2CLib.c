/* 
 * File:   I2CLib.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:28 PM
 */

#include "xc.h"
#include "I2CLib.h"

volatile I2C_STATE_t i2c_state = I2C_IDLE;
buffer_t* rx_buffer; 		// Pointer to the circular buffer

volatile uint8_t i2c_addr;
volatile uint16_t reg_addr;

volatile uint8_t *tx_ptr;
volatile uint8_t *rx_ptr;

volatile uint16_t tx_count;
volatile uint16_t rx_count;

static uint8_t is_read;

volatile uint8_t i2c_busy = 0;

void i2c1_init(buffer_t* rxBuf) {
	// I2C Configuration
	I2C1CON = 0;
	I2C1TRN = 0;
	I2C1STAT = 0;
	I2C1TRN = 0;
    
	// SDA1/SCL1, RP9/RP8 Use Pull Up Mode
	CNPU2bits.CN21PUE = 1;			// Pull Up Mode RP9
	CNPU2bits.CN22PUE = 1;			// Pull Up Mode RP8

	rx_buffer = rxBuf;
	
	// I2C Start
	i2c1_master_init();
	i2c1_slave_init(SLAVE_ADDRESS);

    // ISR Priority Configuration
	_MI2C1IP = 6;

	I2C1CONbits.I2CEN = 1;
}

void i2c1_master_init(void) {
	I2C1BRG = 0x009D;		// 100 kHz @ Tcy = 16 MHz
    I2C1BRG = 0x0025;       // 400 kHz @ Tcy = 16 MHz

	_MI2C1IF = 0;
	_MI2C1IE = 1;
}

void i2c1_slave_init(uint8_t address) {
	I2C1ADD = address;
	I2C1MSK = 0;

	_SI2C1IF = 0;
	_SI2C1IE = 1;
}

void i2c1_wait(void) {
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
          I2C1CONbits.RSEN || I2C1STATbits.TRSTAT);
}

void i2c1_master_writ_stream(uint8_t addr, uint16_t reg, uint8_t *data, uint8_t length) {
    while(i2c_busy); 			// Ensure previous transfer is done
    
    i2c_addr = addr;
	reg_addr = reg;
    tx_ptr = data;
    tx_count = length;

	is_read = 0;

    i2c_busy = 1;
    i2c_state = I2C_START;
    
    I2C1CONbits.SEN = 1;		// Trigger Start Condition
}

void i2c1_master_read_stream(uint8_t addr, uint16_t reg, uint8_t *dest, uint8_t length) {
    while(i2c_busy);			// Ensure previous transfer is done
    
    i2c_addr = addr;
    reg_addr = reg;
    rx_ptr = dest;
    rx_count = length;

	is_read = 1;
    
    i2c_busy = 1;
    i2c_state = I2C_START;
    
    I2C1CONbits.SEN = 1;		// Trigger Start Condition
}

/**
 * Master I2C1 Interrupt Service Routine
 */

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
    // Check for NACK (except during Start/Stop/Restart sequences)
    if (i2c_state != I2C_START && i2c_state != I2C_STOP && I2C1STATbits.ACKSTAT) {
        i2c_state = I2C_STOP;
        I2C1CONbits.PEN = 1; // Force a stop if slave NACKs
        _MI2C1IF = 0;
        return;
    }

    switch (i2c_state) {
        case I2C_START:
            i2c_state = I2C_SEND_ADDR_W;
            I2C1TRN = (i2c_addr << 1); 		// Always start with a Write to set the register
            break;

        case I2C_SEND_ADDR_W:
            i2c_state = I2C_SEND_REG_HI;
            I2C1TRN = (reg_addr >> 8);
            break;

        case I2C_SEND_REG_HI:
            i2c_state = I2C_SEND_REG_LO;
            I2C1TRN = (reg_addr & 0xFF);
            break;

        case I2C_SEND_REG_LO:
            if (is_read) {
                i2c_state = I2C_RESTART;
                I2C1CONbits.RSEN = 1; // Trigger Repeated Start for Reading
            } else {
                if (tx_count > 0) {
                    i2c_state = I2C_TX_DATA;
                    I2C1TRN = *tx_ptr++;
                    tx_count--;
                } else {
                    i2c_state = I2C_STOP;
                    I2C1CONbits.PEN = 1;
                }
            }
            break;

        case I2C_TX_DATA:
            if (tx_count > 0) {
                I2C1TRN = *tx_ptr++;
                tx_count--;
            } else {
                i2c_state = I2C_STOP;
                I2C1CONbits.PEN = 1;
            }
            break;

        case I2C_RESTART:
            i2c_state = I2C_SEND_ADDR_R;
            I2C1TRN = (i2c_addr << 1) | 0x1; // Switch to Read Address
            break;

        case I2C_SEND_ADDR_R:
            i2c_state = I2C_RX_DATA;
            I2C1CONbits.RCEN = 1; // Enable Receiver
            break;

        case I2C_RX_DATA:
            *rx_ptr++ = I2C1RCV;
            rx_count--;
            i2c_state = I2C_SEND_ACK;
            I2C1CONbits.ACKDT = (rx_count <= 0); // NACK if last byte, ACK otherwise
            I2C1CONbits.ACKEN = 1;
            break;

        case I2C_SEND_ACK:
            if (rx_count > 0) {
                i2c_state = I2C_RX_DATA;
                I2C1CONbits.RCEN = 1;
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
            i2c_busy = 0;
            i2c_state = I2C_IDLE;
            break;
    }
    
    _MI2C1IF = 0;
}

/**
 * Slave I2C1 Interrupt Service Routine
 */

void __attribute__((interrupt, auto_psv)) _SI2C1Interrupt(void) {
    uint8_t temp;
    
    _SI2C1IF = 0;
    
    if (I2C1STATbits.R_W == 0) {
        
        if (I2C1STATbits.D_A == 1) {
            // CASE: DATA BYTE RECEIVED
            temp = I2C1RCV;
            buffer_force_push(rx_buffer, temp);
        } else {
            // CASE: ADDRESS MATCH
            temp = I2C1RCV; 
        }

        // Release the clock so the Master can send the next byte
        I2C1CONbits.SCLREL = 1;
    }
}

