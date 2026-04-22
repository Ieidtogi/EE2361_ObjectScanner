/*
 * File:   Main.c
 * Author: ikepr
 *
 * Created on April 9, 2026, 4:00 PM
 */

#include "xc.h"
#include "ASMLib.h"
#include "Button.h"
#include "CirBuf.h"
#include "EEPROM.h"
#include "I2CLib.h"
#include "TOFLib.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
									   // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define true 1
#define false 0

struct buffer_t* myRxBuf;
struct EEPROM* myEEPROM_1;
struct EEPROM* myEEPROM_2;

void setup(void) {
	CLKDIVbits.RCDIV = 0b000;

	AD1PCFG = 0x9FFF;
	
	TRISA = 0x0000;
	TRISB = 0x0000;

	LATA = 0xffff;
	LATB = 0xffff;
	
	myRxBuf = buffer_init();
	myEEPROM_1 = eeprom_init(0x50);
	myEEPROM_2 = eeprom_init(0x51);

	// Initializations
	i2c1_init(myRxBuf);
	tof_init(myEEPROM_1, myEEPROM_2);
}

int main(void) {
	setup();
	unsigned long int count = 0;

    tof_start();
    
    
	while (true) {
		while(tof_get_data()) {
            delay(100);
        }
        matrix;
        count++;
	}
	
}
