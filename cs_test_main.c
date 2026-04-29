/*
 * File:   cs_test_main.c
 * Author: owenk
 *
 * Created on April 15th, 2026, 12:50 AM
 */

#include "xc.h"
#include "color_sensor_lib.h"
#include "oled_lib.h"

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

void InitADC(void);

int main(void) {
    Color_Init();
    Delayms(5); 
    
    spi_init();
    
    while(1) {
        
        short int clearRead = Color_Read(clear); //reads clear data
        Delayms(5);
        short int redRead = Color_Read(red); //reads red data
        Delayms(5);
        short int greenRead = Color_Read(blue); //reads green data
        Delayms(5);
        short int blueRead = Color_Read(green); //reads blue data
        Delayms(25);
        
        for(int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                //fillPixel(redRead,greenRead,blueRead,i,j);
                fillPixel(i+j,i,j,i,j);
            }
        }
        sendCommand(0xAF);
    }
}
