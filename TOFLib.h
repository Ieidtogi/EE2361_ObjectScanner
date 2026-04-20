/* 
 * File:   TOFLib.h
 * Author: Kaibin
 *
 * Created on April 8, 2026, 12:29 PM
 */

#ifndef TOFLIB_H
#define	TOFLIB_H

#include "vl53l5cx_api.h"
#include "EEPROM.h"

#ifdef	__cplusplus
extern "C" {
#endif

	extern VL53L5CX_Configuration 	tof_dev;
	extern VL53L5CX_ResultsData 	tof_results;

	extern EEPROM *fw_eeproms[2];
    extern uint16_t matrix[8][8];
	
	/**
	 * @brief Initializes the VL53L5CX sensor, including firmware upload from EEPROM.
	 * @param eeprom1 Pointer to the first AT24C512 (contains part 0 of firmware)
	 * @param eeprom2 Pointer to the second AT24C512 (contains part 1 of firmware)
	 * @return 0 if success, error code otherwise.
	 */
	uint8_t tof_init(EEPROM *eeprom1, EEPROM *eeprom2);

	/**
	 * @brief Starts the ranging session.
	 */
	uint8_t tof_start(void);

	/**
	 * @brief Stops the ranging session.
	 */
	uint8_t tof_stop(void);

	/**
	 * @brief Checks for data readiness and retrieves results.
	 * @return 1 if new data is available, 0 otherwise.
	 */
	uint8_t tof_get_data(void);
    
    void process_tof_matrix(VL53L5CX_ResultsData *p_results, uint8_t resolution);

#ifdef	__cplusplus
}
#endif

#endif	/* TOFLIB_H */