/* 
 * File:   TOFLib.c
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:29 PM
 */

#include "TOFLib.h"
#include "I2CLib.h"
#include <string.h>

VL53L5CX_Configuration 	tof_dev;
VL53L5CX_ResultsData 	tof_results;

EEPROM *fw_eeproms[2];

uint16_t matrix[8][8];

uint8_t tof_init(EEPROM *eeprom1, EEPROM *eeprom2) {
    uint8_t status = VL53L5CX_STATUS_OK;
    uint8_t is_alive = 0;

    // EEPROM pointers for the platform layer to use
    fw_eeproms[0] = eeprom1;
    fw_eeproms[1] = eeprom2;

    // Configure the Platform Structure
    tof_dev.platform.address = VL53L5CX_DEFAULT_I2C_ADDRESS;
    
    // Hardware Check: Is the sensor there?
    status = vl53l5cx_is_alive(&tof_dev, &is_alive);
    if (status || !is_alive) return VL53L5CX_STATUS_ERROR;

    // Sensor Initialization (Firmware Loading)
    // Note: You must ensure platform.c uses the EEPROM to stream data
    // during this call because the PIC24 cannot hold the FW array.
    status = vl53l5cx_init(&tof_dev);
    if (status) return status;

    // 4. Default Settings
    status |= vl53l5cx_set_resolution(&tof_dev, VL53L5CX_RESOLUTION_8X8);
    status |= vl53l5cx_set_ranging_frequency_hz(&tof_dev, 30); // 30Hz
    status |= vl53l5cx_set_ranging_mode(&tof_dev, VL53L5CX_RANGING_MODE_CONTINUOUS);

    return status;
}

uint8_t tof_start(void) {
    return vl53l5cx_start_ranging(&tof_dev);
}

uint8_t tof_stop(void) {
    return vl53l5cx_stop_ranging(&tof_dev);
}

uint8_t tof_get_data(void) {
    uint8_t ready = 0;
    
    // Check if new data is ready on the sensor
    vl53l5cx_check_data_ready(&tof_dev, &ready);
    
    if (ready) {
        vl53l5cx_get_ranging_data(&tof_dev, &tof_results);
        process_tof_matrix(&tof_results, VL53L5CX_RESOLUTION_8X8);
        return 1;
    }

    return 0;
}

void process_tof_matrix(VL53L5CX_ResultsData *p_results, uint8_t resolution) {
    int i, j;
    uint8_t zones_per_line = (resolution == VL53L5CX_RESOLUTION_4X4) ? 4 : 8;

    for (i = 0; i < zones_per_line; i++) {       // Rows
        for (j = 0; j < zones_per_line; j++) {   // Columns
            // Calculate the 1D index from the 2D coordinates
            int index = (i * zones_per_line) + j;
            
            uint16_t dist = p_results->distance_mm[index];
            
            matrix[i][j] = dist;
            
//            uint8_t status = p_results->target_status[index];
//            if (status == 5 || status == 9) { 
//                // Valid data - 'dist' is the millimeter value in the matrix
//                // You could store this in a 2D array: my_matrix[i][j] = dist;
//            } else {
//                // Invalid data or no target
//            }
        }
    }
}