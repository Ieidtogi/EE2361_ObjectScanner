/* 
 * File:   color_sensor_lib.c
 * Author: owenk
 *
 * Created on April 14, 2026, 5:33 PM
 */

#include "xc.h"
#include "color_sensor_lib.h"

void Color_Init(void) {
    //BP configuration
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATA = 0xffff;               //Set all of port A to HIGH
    LATB = 0xffff;               //and all of port B to HIGH
    
    //I2C1 initialization
    I2C1CON = 0; //disable and reset control register
    I2C1BRG = 157; //FSCL = ~100kHz
    _MI2C1IF = 0; //clear interrupt flag
    I2C1CONbits.I2CEN = 1; //enable
    
    Delayms(5);
    
    //Initialization calls
    Color_Cmd(0x80, 0x00); //clear register
    Delayms(5);
    Color_Cmd(0x80, 0x01); //device enable
//    Color_Cmd(0x80, 0x09); //device enable with wait
    Delayms(5);
    Color_Cmd(0x81, 0xFF); //set 2.4 millisecond RGBC time
    Delayms(5); 
    //Color_Cmd(0x80, 0x12); //RBGC enable PON = 0
    Color_Cmd(0x80, 0x03); //RBGC enable PON = 1
}

void Color_Cmd(char command, char data) {
    I2C1CONbits.SEN = 1;
    while(_SEN); //wait for startup to complete
    
    PrintFrame(address<<1); //sensor address with R/nW = 0
    PrintFrame(command); 
    PrintFrame(data);
    
    I2C1CONbits.PEN = 1;
    while (_PEN); //wait for shutdown to complete
}

int Color_Read(char regAddress) {
    int colorVal = 0;
    
    I2C1CONbits.SEN = 1;
    while(_SEN); //wait for startup to complete

    PrintFrame(address<<1); //sensor address with R/nW = 0
    PrintFrame(regAddress | 0xA0); //calls specified register with auto-increment
    
    I2C1CONbits.SEN = 1; //repeated start condition
    while(_SEN); //wait for startup to complete
    PrintFrame(address<<1 | 1); //re-address with R/nW = 1
    colorVal = GetByte(); //add lower byte
//    colorVal += GetByte()<<8; //add upper byte
    
    I2C1CONbits.PEN = 1;
    while (_PEN); //wait for shutdown to complete
    
    return(colorVal);
}

void PrintFrame(char byte) {
    _MI2C1IF = 0;
    I2C1TRN = byte;
    while ((!_MI2C1IF) & _TRSTAT & (!_ACKSTAT)); //waits for transmission to finish 
}

char GetByte(void){
    _RCEN = 1; //activate receive mode
//    while(!_RBF);
    while(!_RBF & _RCEN); //wait for receive to complete
    _ACKEN = 1; //send acknowledge bit
//    while(_ACKEN);
    return(I2C1RCV);
}

void Delayms(int time) {
    for(int i=0;i<time;i++) {
        for(int j=0;j<2000;j++){
            //loop
        }
    }
}