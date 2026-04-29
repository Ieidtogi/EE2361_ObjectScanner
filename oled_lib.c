
/*
 * File:   oled_main.c
 * Author: djlep
 *
 * Created on April 15, 2026, 6:52 PM
 */
#include <p24Fxxxx.h>
#include <xc.h>
#include <stdlib.h>
#include "oled_lib.h"

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
    SPI1CON1bits.PPRE = 0b01;  // primary prescaler = 64;
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
    
    for(int i = 0; i<170; i++){
        for(int j =0; j<170;j++){
            for(int k = 0; k<171;k++){
            }
        }
    }
    
    int temp;
    // turn on the OLED
    sendCommand(0xA6); // set display to regular grayscale
    sendCommand(0xAF); // turn off sleep mode

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

void sendData(int data) {
    int temp;
    _LATA3 = 1;
    SPI1BUF = data;
    while (!_SPI1IF);
    temp = SPI1BUF;
    _SPI1IF = 0;
}

void fillPixel(short int red, short int green, short int blue, int x, int y) {
    
    setPos(x*16,y*16,x*16+15,y*16+15);
    
    for(int i = 0; i < 16*16; i++) {
        sendColor(red,green,blue);
    }
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
    sendData((high_blue<<6)+(medium_blue<<4)+(low_blue<<2)+high_green);
    sendData((medium_green<<6)+(low_green<<4)+(high_red<<2)+medium_red);
    sendData((low_red<<6)+0b111);

}