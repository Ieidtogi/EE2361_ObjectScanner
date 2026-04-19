/*******************************************************************************
* Copyright (c) 2020, STMicroelectronics - All Rights Reserved
*
* This file is part of the VL53L5CX Ultra Lite Driver and is dual licensed,
* either 'STMicroelectronics Proprietary license'
* or 'BSD 3-clause "New" or "Revised" License' , at your option.
*
********************************************************************************
*
* 'STMicroelectronics Proprietary license'
*
********************************************************************************
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms at www.st.com/sla0081
*
* STMicroelectronics confidential
* Reproduction and Communication of this document is strictly prohibited unless
* specifically authorized in writing by STMicroelectronics.
*
*
********************************************************************************
*
* Alternatively, the VL53L5CX Ultra Lite Driver may be distributed under the
* terms of 'BSD 3-clause "New" or "Revised" License', in which case the
* following provisions apply instead of the ones mentioned above :
*
********************************************************************************
*
* License terms: BSD 3-clause "New" or "Revised" License.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*
*******************************************************************************/

#include "ASMLib.h"
#include "I2CLib.h"
#include "TOFLib.h"
#include "platform.h"

uint8_t RdByte(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAddr,
		uint8_t *p_value)
{
	i2c1_master_read_stream(p_platform->address, RegisterAddr, p_value, 1);

	// Wait for ISR to complete
    while(i2c_busy);
	return 0;
}

uint8_t WrByte(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAddr,
		uint8_t value)
{
	i2c1_master_writ_stream(p_platform->address, RegisterAddr, &value, 1);

	// Wait for ISR to complete
    while(i2c_busy);
	return 0;
}

uint8_t WrMulti(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAddr,
		uint8_t *p_values,
		uint16_t size)
{
	i2c1_master_writ_stream(p_platform->address, RegisterAddr, p_values, size);
    
    // Wait for ISR to complete
    while(i2c_busy);
	return 0;
}

uint8_t RdMulti(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAddr,
		uint8_t *p_values,
		uint16_t size)
{
	i2c1_master_read_stream(p_platform->address, RegisterAddr, p_values, size);

	// Wait for ISR to complete
    while(i2c_busy);
    return 0;
}

uint8_t WrEEPROM(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAddr,
		uint32_t EEPROMAddr,
		uint16_t size
)
{
	uint32_t cur_addr = EEPROMAddr;
    uint16_t remaining = size;
    uint16_t chunk;

    while(remaining > 0) 
    {
        uint8_t buffer[128];
        chunk = (remaining > 128) ? 128 : remaining;

        // Select EEPROM and calculate local offset
        // EEPROM 0: 0x00000 - 0x0FFFF
        // EEPROM 1: 0x10000 - 0x1FFFF
        EEPROM *target_eeprom = (cur_addr < 0x10000) ? fw_eeproms[0] : fw_eeproms[1];
        uint16_t local_offset = (uint16_t)(cur_addr & 0xFFFF);

        // Read from EEPROM
        i2c1_master_read_stream(target_eeprom->addr, local_offset, buffer, chunk);
        while(i2c_busy);

        // Write to sensor (Register address increments inside the sensor)
        i2c1_master_write_stream(p_platform->address, RegisterAddr, buffer, chunk);
        while(i2c_busy);

        cur_addr += chunk;
        remaining -= chunk;
    }

    return 0;
}

// uint8_t WrFW(VL53L5CX_Platform *p_platform, uint32_t addr, uint16_t size)
// {
// 	EEPROM cur_eeprom = *fw_eeproms[0];
// 	uint32_t cur_addr = addr;
// 	uint16_t count = size;

// 	uint8_t buffer[128] = 0;

// 	while(count > 0)
// 	{
// 		if (cur_addr > 0xFFFF)
// 		{
// 			cur_eeprom = *fw_eeproms[1];
// 		}
		
// 		// Read data from EEPROM
// 		i2c1_master_read_stream(cur_eeprom.addr, (uint16_t)cur_addr, &buffer, 128);
// 		while(i2c_busy);

// 		// Stream data to sensor
// 		i2c1_master_writ_stream(p_platform->address, 0, &buffer, 128);

// 		cur_addr += 128;
// 		count -= 128;
// 	}

// 	// Wait for ISR to complete
//     while(i2c_busy);
// 	return 0;
// }

uint8_t Reset_Sensor(
		VL53L5CX_Platform *p_platform)
{
	/* (Optional) Need to be implemented by customer. This function returns 0 if OK */
	
	/* Set pin LPN to LOW */
	/* Set pin AVDD to LOW */
	/* Set pin VDDIO  to LOW */
	WaitMs(p_platform, 100);

	/* Set pin LPN of to HIGH */
	/* Set pin AVDD of to HIGH */
	/* Set pin VDDIO of  to HIGH */
	WaitMs(p_platform, 100);

	return 0;
}

void SwapBuffer(
		uint8_t 		*buffer,
		uint16_t 	 	 size)
{
	uint16_t i, tmp;
	
	/* Example of possible implementation using <string.h> */
	for(i = 0; i < size; i = i + 4) 
	{
		tmp = (
		  buffer[i]<<24)
		|(buffer[i+1]<<16)
		|(buffer[i+2]<<8)
		|(buffer[i+3]);
		
		memcpy(&(buffer[i]), &tmp, 4);
	}
}	

uint8_t WaitMs(
		VL53L5CX_Platform *p_platform,
		uint16_t TimeMs)
{
	for (size_t i = 0; i < TimeMs; i++) {
		delay1m();
	}

	return 0;
}
