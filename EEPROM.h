/* 
 * File:   EEPROM.h
 * Author: Kaibin
 *
 * Created on April 10, 2026, 12:30 PM
 */

#include <stdlib.h>

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
	
	/* EEPROM Struct */
	typedef struct EEPROM {
		unsigned char addr;
		int size;
		int page;
	} EEPROM;

	struct EEPROM* eeprom_init(unsigned char addr);

	unsigned char eeprom_addr(EEPROM* eeprom);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */