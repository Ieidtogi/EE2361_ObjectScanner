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
    
    #define address 0b0101001
    #define lowerByte 0
    #define upperByte 1
    #define clear 0x14
    #define red 0x16
    #define green 0x18
    #define blue 0x1A


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

