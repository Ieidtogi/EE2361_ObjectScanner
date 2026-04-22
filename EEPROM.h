/* 
 * File:   EEPROM.h
 * Author: Kaibin
 *
 * Created on April 10, 2026, 12:30 PM
 */

#include <stdlib.h>
#include <stdint.h>

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
	
	/* EEPROM Struct */
	typedef struct EEPROM {
		uint8_t addr;
	} EEPROM;

	struct EEPROM* eeprom_init(uint8_t addr);

	unsigned char eeprom_addr(EEPROM* e);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */