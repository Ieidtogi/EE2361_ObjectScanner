/*
 * File:   Main.c
 * Author: ikepr
 *
 * Created on April 9, 2026, 4:00 PM
 */


#include "xc.h"
#include "CirBuf.h"
#include "I2CLib.h"
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

#define turnon 0xAF

buffer_t* myBuf;

unsigned long int count = 0;

void setup(void) {
    //setup stuff
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    
    myBuf = buffer_init();
    i2c1_init(myBuf);
    
    Color_Init();
    initButton();
}

int main(void) {
    setup();
    
    _TRISA4 = 0;
    
    LATAbits.LATA4 = 0;
    
    for(int i = 0; i < 10; i++) {
        for (unsigned int i = 0; i < 65535; i++);
    }
    
    LATAbits.LATA4 = 1;
    
    LATAbits.LATA4 = 0;
    
    for(int i = 0; i < 175; i++) {
        for (unsigned int i = 0; i < 65535; i++);
    }
    
    LATAbits.LATA4 = 1;
    
    spi_init();
    
    int red=0;
    int green=0;
    int blue=0;
    
    sendCommand(0xA6);
    int testRed = 63;
    int testGreen = 0;
    int testBlue = 0;
    short int temp = 0;
    
    while(1) {
        sendCommand(turnon);    // Turn on the OLED display repeatedly again just in case.

        // TODO: Button Logic Implementation

//        if(isButtonPressed) {
//            // Scan -> Display
//          short int clearRead = Color_Read(clearReg); // reads clear data
//          Delayms(5);
//          short int redRead = Color_Read(redReg); // reads red data
//          Delayms(5);
//          short int greenRead = Color_Read(blueReg); // reads green data
//          Delayms(5);
//          short int blueRead = Color_Read(greenReg); // reads blue data
//          Delayms(25);
//        } else {  
//
//        }

        // Debug Test Logic
        
//        temp &= 0b111111;
//        
//        fillPixel(31,31,32,0,0);
//        
//        temp++;

//        for (int i = 0; i < 8;i++) {
//            for (int j = 0; j < 8; j++) {
//                fillPixel(63,0,0,i,j);
//            }
//        }
//
//        sendCommand(turnon);
//        for (int i = 0; i < 8;i++) {
//            for (int j = 0; j < 8; j++) {
//                fillPixel(0,63,0,i,j);
//            }
//        }
//        sendCommand(turnon);
//        for (int i = 0; i < 8;i++) {
//            for (int j = 0; j < 8; j++) {
//                fillPixel(0,0,63,i,j);
//            }
//        }
        
//        sendCommand(turnon);
//        for (int i = 0; i < 8;i++) {
//            for (int j = 0; j < 8; j++) {
//                int t = 4*(i + j);
//                fillPixel(t,t,t,i,j);
//            }
//        }
          
        sendCommand(turnon);
        
        for(int i = 0; i < 16000;i++);
        
        sendCommand(0xA5);
        
        for(int i = 0; i < 16000;i++);

        sendCommand(0xA6);
        
        for(int i = 0; i < 16000;i++);
        
        for(int i = 0; i < 100; i++) {
            for(int j = 0; j < 32000; j++) {
                asm("NOP");
            }
        }
        
        data_conversion(myBuf);
//        
//        count++;
//        
//        testBlue = testGreen;
//        testGreen = testRed;
//        testRed = temp;
//        temp = testBlue;
//        fillScreen(redRead, greenRead, blueRead, nor_results);

        fillScreen(63, 63, 63, nor_results);
        
        count++;
        
        fillScreen(63, 63, 63, nor_results);

//        if(isButtonPressed) {
//            //Scan -> Display
//            
//            
//        } 
//        else {
//            sendCommand(0x5D);
//        }
    }
}
