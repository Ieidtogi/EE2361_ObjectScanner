/* 
 * File:   I2CLib.h
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:39 PM
 */

#ifndef I2CLIB_H
#define	I2CLIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
	/* I2C State Machine Definition Struct */
	typedef enum {
		I2C_IDLE,
		I2C_START,
		I2C_SEND_ADDR,
		I2C_SEND_CONTROL,
		I2C_SEND_DATA,
		I2C_STOP
	} I2C_STATE_t;

	/* I2C Function Prototype */
	void i2c1_init(void);

	void i2c1_start(void);
	void i2c1_stop(void);

	void i2c1_wait(void);

	void i2c1_master_init(void);
	void i2c1_slave_init(unsigned char address);

	void i2c1_master_write_isr_start(unsigned char addr, unsigned char ctrl, unsigned char data);

	void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void);
	void __attribute__((interrupt, auto_psv)) _SI2C1Interrupt(void);

	/* External Buffer Variable */

#ifdef	__cplusplus
}
#endif

#endif	/* I2CLIB_H */