/* 
 * File:   EEPROM.c
 * Author: Kaibin
 *
 * Created on April 10, 2026, 12:30 PM
 */

#include "EEPROM.h"

struct EEPROM* eeprom_init(unsigned char addr) {
	struct EEPROM* eeprom = malloc(sizeof(struct EEPROM));
	eeprom->addr = addr;
	return eeprom;
}

unsigned char eeprom_addr(EEPROM* eeprom) {
	return eeprom->addr;
}
