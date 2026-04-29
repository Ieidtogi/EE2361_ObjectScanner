/* 
 * File:   oled_lib.h
 * Author: djlep
 *
 * Created on April 15, 2026, 6:52 PM
 */

#ifndef OLED_LIB_H
#define	OLED_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    void sendColor(short int red, short int green, short int blue);
    void sendData(short int data);
    void sendCommand(short int cmd);
    void setPos(short int xStart, short int yStart, short int xEnd, short int yEnd);
    void spi_init(void);
    void fillPixel(short int red, short int green, short int blue, int x, int y);
#ifdef	__cplusplus
}
#endif

#endif	/* OLED_LIB_H */
