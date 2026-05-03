/* 
 * File:   color_sensor_lib.c
 * Author: owenk
 *
 * Created on April 14, 2026, 5:33 PM
 */

#include "xc.h"
#include "color_sensor_lib.h"
#include "I2CLib.h"

void Color_Init(void) {
    //BP configuration
    TRISA |= 0b0000000000011111;  //set port A to inputs, 
    TRISB |= 0b0000000000000011;  //and port B to outputs

    //I2C2 initialization
    I2C2CON = 0; //disable and reset control register
    I2C2BRG = 157; //FSCL = ~100kHz
    _MI2C2IF = 0; //clear interrupt flag
    I2C2CONbits.I2CEN = 1; //enable
    
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
    while(i2c_busy);
    i2c_busy = 1;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN); //wait for startup to complete
    
    PrintFrame(CSaddress<<1); //sensor address with R/nW = 0
    PrintFrame(command); 
    PrintFrame(data);
    
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN); //wait for shutdown to complete
    
    i2c_busy = 0;
}

int Color_Read(char regAddress) {
    while(i2c_busy);
    i2c_busy = 1;
    int colorVal = 0;
        
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN); //wait for startup to complete

    PrintFrame(CSaddress<<1); //sensor address with R/nW = 0
    PrintFrame(regAddress | 0xA0); //calls specified register with auto-increment
    
    I2C2CONbits.SEN = 1; //repeated start condition
    while(I2C2CONbits.SEN); //wait for startup to complete
    PrintFrame(CSaddress<<1 | 1); //re-address with R/nW = 1
    colorVal = GetByte(lowerByte); //add lower byte
    colorVal += GetByte(upperByte)<<8; //add upper byte
    
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN); //wait for shutdown to complete
    
    colorVal = (colorVal>>2) & 0b111111; //truncates value to 6 bits
    i2c_busy = 0;
    return(colorVal);
}

void PrintFrame(char byte) {
    _MI2C2IF = 0;
    I2C2TRN = byte;
    while ((!_MI2C2IF) & I2C2STATbits.TRSTAT & (!I2C2STATbits.ACKSTAT)); //waits for transmission to finish 
}

char GetByte(int byte){
    I2C2CONbits.RCEN = 1; //activate receive mode
    while(!I2C2STATbits.RBF & I2C2CONbits.RCEN); //wait for receive to complete
    int temp = I2C2RCV;
    if(byte == lowerByte) { //sends ACK to continue transmission for upper byte
        I2C2CONbits.ACKEN = 1; //send acknowledge bit
        while(I2C2CONbits.ACKEN);
    }
    
    else if(byte == upperByte) { //sends NACK to end receive transmission
        I2C2CONbits.ACKDT = 1; //sets acknowledge to NACK
        I2C2CONbits.ACKEN = 1; //send acknowledge bit
        while(I2C2CONbits.ACKEN); 
        I2C2CONbits.ACKDT = 0; //sets acknowledge back to ACK
    }
    
    return(I2C2RCV);
}

void Delayms(int time) {
    for(int i=0;i<time;i++) {
        for(int j=0;j<2000;j++){
            //loop
        }
    }
}

//long int GetRGB(void) { 
//    long int colorVal = (Color_Read(0x16)>>6) & 0b111111;
////    colorVal +=
//}