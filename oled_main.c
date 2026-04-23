/*
 * File:   oled_main.c
 * Author: djlep
 *
 * Created on April 15, 2026, 6:52 PM
 */
#include <p24Fxxxx.h>
#include <xc.h>
#include <stdlib.h>

// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled. 
					// Primary Oscillator refers to an external osc connected to the OSC1 and OSC2 pins)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#include "xc.h"

#define write 0x5C

//volatile unsigned short int sample = DACBITS;

//void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void)
//{
//    sample &= DACMASK;
//    sample |= DACBITS;
//
//    IFS0bits.T2IF = 0;
//    SPI1BUF = sample;   // Kickstart the SPI transaction. Do not worry about
//                        // LDAC' now. We will get the SPI interrupt once
//                        // the last bit is out. We will generate a pulse 
//                        // on the LDAC' line then.
//    
//    sample += 41;       // the next "step" value.
//}


void spi_init(void)
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;  // For digital I/O.  If you want to use analog, you'll
                       // need to change this.
//    TRISB = 0;    // make all PORTBbits outputs initially
    
    // add your configuration commands below
    TRISBbits.TRISB4 = 0; // SCK
    TRISBbits.TRISB5 = 0; // SDO
    TRISAbits.TRISA3 = 0; // Data or Command
    _LATA4 = 1;
    TRISAbits.TRISA4 = 1; // Reset
    _CN0PUE = 1;

    T2CON = 0;
    PR2 = 3200; // Period of step will be 300 Tcy = 18.75 us
    T2CONbits.TON = 1;

    // Peripheral Pin Select 
    // Ver 1.25 or later
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR2bits.RP5R = 7;   //RB5->SPI1:SDO1; See Table 10-3 on P109 of the datasheet
    RPOR2bits.RP4R = 8;   //RB4->SPI1:SCK1OUT;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    SPI1CON1 = 0;
    SPI1CON1bits.MSTEN = 1;  // master mode
    SPI1CON1bits.MODE16 = 0; // 8 bits
    SPI1CON1bits.CKE = 1;
    SPI1CON1bits.CKP = 0;
    SPI1CON1bits.SPRE = 0b0; // secondary prescaler = 8 
    SPI1CON1bits.PPRE = 0b0;  // primary prescaler = 64;
    // SPI1CON1bits.PPRE = 0b01;  // primary prescaler = 16;
    SPI1CON2 = 0;
    SPI1STAT = 0;
    SPI1STATbits.SISEL = 0b101; // IF set when last bit is shifted out
                                // That means the SPI xfer is complete.
    SPI1STATbits.SPIEN = 1;


//    IFS0bits.T2IF = 0;
//    TMR2 = 0;
//
//    IPC1bits.T2IP = 5;
//    IEC0bits.T2IE = 1;
    _SPI1IF = 0;
//    _SPI1IE = 1;

    // Reset the OLED
    _TRISA4 = 1;
    for (int i = 0; i<100;i++);
    _TRISA4 = 0;
    
    int temp;
    // turn on the OLED
    sendCommand(0xAF);
    sendCommand(0xA5); // set display to regular grayscale
}

void setPos(short int xStart, short int yStart, short int xEnd, short int yEnd) {
    sendCommand(0x15); // set column address command
    sendData(xStart); // send the start column address
    sendData(xEnd); // send the end column address
    sendCommand(0x75); // set row address command
    sendData(yStart); // send the start column address
    sendData(yEnd); // send the end column address
}

void sendCommand(short int cmd) {
    int temp;
    _LATA3 = 0;
    SPI1BUF = cmd;
    while (!_SPI1IF);
    temp = SPI1BUF;
    _SPI1IF = 0;
}

void sendData(short int data) {
    int temp;
    _LATA3 = 1;
    SPI1BUF = data;
    while (!_SPI1IF);
    temp = SPI1BUF;
    _SPI1IF = 0;
}

// Sends 4 pixels of the given color
void sendColor(short int red, short int green, short int blue) {
    
    int high_red = red >> 4;
    int medium_red = (red & 0b001100) >> 2;
    int low_red = red & 0b000011;
    
    int high_green = green >> 4;
    int medium_green = (green & 0b001100) >> 2;
    int low_green = green & 0b000011;
    
    int high_blue = blue >> 4;
    int medium_blue = (blue & 0b001100) >> 2;
    int low_blue = blue & 0b000011;
    
    sendCommand(write);
    sendData(high_red<<6+medium_red<<4+low_red<<2+high_green);
    sendData(medium_green<<6+low_green<<4+high_blue<<2+medium_blue);
    sendData(low_blue<<6+high_red<<4+medium_red<<2+low_red);
    sendData(high_green<<6+medium_green<<4+low_green<<2+high_blue);
    sendData(medium_blue<<6+low_blue<<4+high_red<<2+medium_red);
    sendData(low_red<<6+high_green<<4+medium_green<<2+low_green);
    sendData(high_blue<<6+medium_blue<<4+low_blue<<2+high_red);
    sendData(medium_red<<6+low_red<<4+high_green<<2+medium_green);
    sendData(low_green<<6+high_blue<<4+medium_blue<<2+low_blue);

}

int main(void) {
    
    spi_init();
    for (int i = 0; i < 6000; i++);
    sendCommand(0xA6);
    setPos(0, 0, 60, 31);
    sendCommand(0x5C);
    for(int i = 0; i < 999; i++) {
        sendColor(0,48,0);
    }
    
//    sendCommand(0x5D);
    while(1) {
//        setPos(64, 0, 127, 127);
//        sendCommand(0x5C);
//        sendData(0x0);
//        sendData(0x0);
//        sendCommand(0x5D);
        
//        setPos(10, 10, 20, 20);
//        sendCommand(0x5C);
//        sendData(0x40);
//        sendData(0xFF);
//        sendData(0x04);

//        
//        setPos(40, 40, 20, 20);
//        sendCommand(0x5C);
//        sendData(0x40);
        
//        setPos(30, 10, 40, 20);
//        sendCommand(0x5C);
//        sendData(0xFF);
//        sendData(0x0);
//        sendData(0x0);
    }
    return 0;
}
