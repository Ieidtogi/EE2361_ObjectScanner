/* 
 * File:   I2CLib.h
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:39 PM
 */

#ifndef I2CLIB_H
#define	I2CLIB_H

#include <stdint.h>
#include "CirBuf.h"

#define SLAVE_ADDRESS 0x10

#ifdef	__cplusplus
extern "C" {
#endif
    
	/* I2C State Machine Definition Struct */
	typedef enum {
		I2C_IDLE,
		I2C_START,
		I2C_SEND_ADDR_W,
		I2C_SEND_REG_HI,
		I2C_SEND_REG_LO,
		I2C_TX_DATA,        // For WrMulti (Write Stream)
		I2C_RESTART,        // For RdMulti (Repeated Start)
		I2C_SEND_ADDR_R,    // For RdMulti
		I2C_RX_DATA,        // For RdMulti (Read Stream)
		I2C_SEND_ACK,       // For RdMulti
		I2C_STOP
	} I2C_STATE_t;

	extern uint8_t i2c_busy = 0;
	extern const buffer_t *rx_buffer;

	/* I2C Function Prototype */
	void i2c1_init(buffer_t *rxBuf);

	void i2c1_master_init(void);
	void i2c1_slave_init(uint8_t address);

	void i2c1_master_writ_stream(uint8_t addr, uint16_t reg, uint8_t *data, uint8_t length);
	void i2c1_master_read_stream(uint8_t addr, uint16_t reg, uint8_t *dest, uint8_t length);

	void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void);
	void __attribute__((interrupt, auto_psv)) _SI2C1Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2CLIB_H */