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

    void PrintFrame(char byte);
    char GetByte(void);
    void Color_Init(void);
    void Color_Cmd(char command, char data);
    int Color_Read(char regAddress);
    void Delayms(int time);


#ifdef	__cplusplus
}
#endif

#endif	/* COLOR_SENSOR_LIB_H */

