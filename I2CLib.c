/* 
 * File:   I2CLib.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:28 PM
 */

#include "xc.h"
#include "I2CLib.h"

volatile I2C_STATE_t i2c_state = I2C_IDLE;

volatile unsigned char i2c_addr;
volatile unsigned char i2c_control;
volatile unsigned char i2c_payload;
volatile unsigned int i2c_read = 0;
volatile int i2c_busy = 0;

void i2c1_init(void) {
	// I2C Configuration
	I2C1CON = 0;
	I2C1TRN = 0;
	I2C1STAT = 0;
	
	// SDA1/SCL1, RP9/RP8 Use Pull Up Mode
	CNPU2bits.CN21PUE = 1;			// Pull Up Mode RP9
	CNPU2bits.CN22PUE = 1;			// Pull Up Mode RP8
	
	// I2C Start
	I2C1_Master_Init();
	I2C1_Slave_Init(MASTER_ADDRESS);
		
	_MI2C1IF = 0;
	_MI2C1IE = 1; 
	
	I2C1CONbits.I2CEN = 1;
}

void i2c1_master_write_isr_start(unsigned char addr, unsigned char ctrl, unsigned char data) {
	while(i2c_busy); // Ensure previous transfer is done
	
	i2c_addr = addr << 1;
	i2c_control = ctrl;
	i2c_payload = data;
	i2c_busy = 1;
	i2c_state = I2C_START;
	
	I2C1CONbits.SEN = 1; // Trigger Start Condition
}

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
			i2c_state = I2C_SEND_CONTROL;
			I2C1TRN = i2c_control;
			break;

		case I2C_SEND_CONTROL:
			i2c_state = I2C_SEND_DATA;
			I2C1TRN = i2c_payload;
			break;

		case I2C_SEND_DATA:
			i2c_state = I2C_STOP;
			I2C1CONbits.PEN = 1;	// Trigger Stop
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
	_MI2C1IF = 0;					// Clear interrupt flag
}

/**
 * Slave I2C1 Interrupt Service Routine
 */

void __attribute__((interrupt, auto_psv)) _SI2C1Interrupt(void) {
	unsigned char temp;
	if (I2C1STATbits.R_W == 0 && I2C1STATbits.D_A == 0) {
		// Address matched, Master wants to Write
		temp = I2C1RCV;     // Dummy read to clear buffer
	} else if (I2C1STATbits.D_A == 1) {
		// Data byte received
		temp = I2C1RCV;     // Actual data received from Master
	}
	_SI2C1IF = 0;           // Clear interrupt flag
}

