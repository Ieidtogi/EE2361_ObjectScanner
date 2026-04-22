/* 
 * File:   EEPROM.c
 * Author: Kaibin
 *
 * Created on April 10, 2026, 12:30 PM
 */

#include "EEPROM.h"

struct EEPROM* eeprom_init(uint8_t addr) {
	struct EEPROM* e = malloc(sizeof(struct EEPROM));
    
	if (e != NULL) {
        e->addr = addr;
    }
    
	return e;
}

uint8_t eeprom_addr(EEPROM* e) {
	return e->addr;
}
