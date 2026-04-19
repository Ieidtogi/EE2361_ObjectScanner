/* 
 * File:   EEPROM.c
 * Author: Kaibin
 *
 * Created on April 10, 2026, 12:30 PM
 */

#include "EEPROM.h"

struct EEPROM* eeprom_init(unsigned char addr, int size, int page) {
	struct EEPROM* eeprom = malloc(sizeof(struct EEPROM));
	eeprom->addr = addr;
	eeprom->size = size;
	eeprom->page = page;
	return eeprom;
}

unsigned char eeprom_addr(EEPROM* eeprom) {
	return eeprom->addr;
}

int eeprom_size(EEPROM* eeprom) {
	return eeprom->size;
}

int eeprom_page(EEPROM* eeprom) {
	return eeprom->page;
}