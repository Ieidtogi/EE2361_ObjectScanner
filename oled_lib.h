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
    void sendColor(short int red, short int green, short int blue); // fill a single pixel with an RGB value
    void sendData(short int data); // send 8 bits of data to the OLED
    void sendCommand(short int cmd); // send an 8 bit command to the OLED
    void setPos(short int xStart, short int yStart, short int xEnd, short int yEnd); // designate a square on the OLED to fill with a color
    void spi_init(void); // initialize serial communications for the OLED
    void fillPixel(short int red, short int green, short int blue, int x, int y); // split the OLED into an 8x8 grid and fill one area with one color
#ifdef	__cplusplus
}
#endif

#endif	/* OLED_LIB_H */
