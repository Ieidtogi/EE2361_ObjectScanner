
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
#define y_offset 6*16
#define A0_DATA 0b01110111

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
    
    SPI1CON1bits.CKE = 1;               // Kaibin: Changed this to 0 acc to datasheet
    SPI1CON1bits.CKP = 0;               // Kaibin: Changed this to 1 acc to datasheet
    SPI1CON1bits.SMP = 1;               // Added new line
    
    SPI1CON1bits.SPRE = 0b01; // secondary prescaler = 8 
    SPI1CON1bits.PPRE = 0b01;  // primary prescaler = 64;
    // SPI1CON1bits.PPRE = 0b01;  // primary prescaler = 16;
    SPI1CON2 = 0;
    SPI1STAT = 0;
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SISEL = 0b101; // IF set when last bit is shifted out
                                // That means the SPI xfer is complete.
    SPI1STATbits.SPIEN = 1;
    
    _SPI1IF = 0;
    // turn on the OLED
    int temp = SPI1BUF;
    sendCommand(0xA0);
    sendData(A0_DATA); // Horizontal Address increment | Column 0 is 0 | Color Sequence RGB | Scan from COM[0 to n-1] | 16 bit format
    sendCommand(0xFD); // Command lock or unlock command
    sendCommand(0x12); // unlock command
    
    sendCommand(0xA6); // set display to regular grayscale
    sendCommand(0xAF); // turn off sleep mode

}

void setPos(short int xStart, short int yStart, short int xEnd, short int yEnd) {
    // Allocate the square you would like to color
    sendCommand(0x15); // set column address command
    sendData(xStart); // send the start column address
    sendData(xEnd); // send the end column address
    sendCommand(0x75); // set row address command
    sendData(yStart); // send the start column address
    sendData(yEnd); // send the end column address
}

void sendCommand(short int cmd) {
    short int temp;
    _SPIROV = 0;
    _LATA3 = 0; // This tells the OLED that the data coming in is a command
    
    while (SPI1STATbits.SPITBF); // make sure the buffer will not overflow
    
    SPI1BUF = cmd; // send the command
    
    while (!SPI1STATbits.SPIRBF);
    while (!_SPI1IF); // wait for the command to be sent
    temp = SPI1BUF; // clear the buffer
    _SPI1IF = 0;
}

void sendData(short int data) { 
    short int temp;
    _SPIROV = 0;
    _LATA3 = 1; // this tells the OLED that the data coming in is just data
    
    while (SPI1STATbits.SPITBF); // make sure the buffer will not overflow
    
    SPI1BUF = data; // send the data
    
    while (!SPI1STATbits.SPIRBF);
    while (!_SPI1IF); // wait for the data to be sent
    temp = SPI1BUF; // clear the buffer
    _SPI1IF = 0;
}

void fillPixel(short int red, short int green, short int blue, int x, int y) {
    // splits the screen into an 8x8 grid of pixels, and fills a single one with the given color
    setPos(x*16,(y*16+y_offset)%128,x*16+15,(y*16+15+y_offset)%128); // an 8x8 grid on the OLED would mean 16x16 pixel chunks
    
    for(int i = 0; i < 256; i++) {
        sendColor(red,green,blue);
    } // fills the pixel with the given color
}


void sendColor(short int red, short int green, short int blue) {
    // Gives a single pixel on the screen a color.
    short int trueRed = red >> 1;
    short int high_green = green >> 3;
    short int low_green = green & 0b000111;
    short int trueBlue = blue >> 1; // reformat the color values for 5 6 5 16bit R G B format
    sendCommand(write);
    sendData(0x00 | ((trueRed<<3)) | (high_green));
    sendData(0x00 | ((low_green<<5) | (trueBlue)));
}

void fillScreen(short int red, short int green, short int blue, float distances[8][8]) {
    // Takes a 2D array of distances and adjusts the brightness of the color according to their position. Giving the illusion of a 3D image
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            float temp = distances[i][j];
            short int redr = (int)(red * (1.0f - temp));
            short int greenr = (int)(green * (1.0f - temp));
            short int bluer = (int)(blue * (1.0f - temp));
            fillPixel(redr, greenr, bluer, i, j);
        }
    }
}