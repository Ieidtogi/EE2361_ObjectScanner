/*
 * File:   Main.c
 * Author: ikepr
 *
 * Created on April 9, 2026, 4:00 PM
 */


#include "xc.h"
#include "Button.h"
#include "oled_lib.h"
#include "color_sensor_lib.h"

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

void setup(void) {
    //setup stuff
}

int main(void) {
    
    setup();
    Color_Init();
    Delayms(5); 

    initButton();
    
    spi_init();
    for (int i = 0; i < 6000; i++);
    sendCommand(0xA6);
    setPos(0, 0, 60, 31);
    sendCommand(0x5C);
    for(int i = 0; i < 9999; i++) {
//        sendColor(0,48,0);
        sendData(0x5C);
    }
//    sendCommand(0x5D);
    sendCommand(0x5C);
    while(1) {
        if(isButtonPressed) {
            //Scan -> Display
//            sendData(0x0C);
            sendColor(0,0,5);
            
            I2C1CONbits.SEN = 1;
            while(_SEN); //wait for startup to complete

            PrintFrame(address<<1);

            I2C1CONbits.PEN = 1;
            while (_PEN); //wait for shutdown to complete

            // int clear = Color_Read(0x14); //reads clear data
            Delayms(5);
        }
        if(!isButtonPressed) {
            sendColor(0,5,0);
        }
    }
}
