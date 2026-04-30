/* 
 * File:   color_sensor_lib.h
 * Author: owenk
 *
 * Created on April 14, 2026, 5:33 PM
 */

#ifndef COLOR_SENSOR_LIB_H
#define	COLOR_SENSOR_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define CSaddress 0b0101001
    #define lowerByte 0
    #define upperByte 1
    #define clearReg 0x14
    #define redReg 0x16
    #define greenReg 0x18
    #define blueReg 0x1A


    void PrintFrame(char byte);
    char GetByte(int byte);
    void Color_Init(void);
    void Color_Cmd(char command, char data);
    int Color_Read(char regAddress);
    void Delayms(int time);
    long int GetRGB(void);

#ifdef	__cplusplus
}
#endif

#endif	/* COLOR_SENSOR_LIB_H */

