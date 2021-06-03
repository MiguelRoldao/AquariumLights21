/*
 * $projectname$.cpp
 *
 * Created: $date$
 * Author : $user$
 */ 

#include <stdint.h>
#include <i2c.h>
#include <pcf8574.h>



uint8_t pcf8574_genericbits(uint8_t addr, uint8_t ored, uint8_t anded)
{
	uint8_t data;
	if (pcf8574_read(addr, &data)) return 1;
	data = (data & anded) | ored;
	if (pcf8574_write(addr, &data)) return 1;
	return 0;
}

