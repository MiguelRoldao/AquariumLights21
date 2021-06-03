/*
 * $projectname$.c
 *
 * Created: $date$
 * Author : $user$
 */ 

#ifndef _PCF8574_H_
#define _PCF8574_H_

#include <stdint.h>
#include <i2c.h>

#define PCF8574_ADDR 0x20


inline uint8_t	pcf8574_write		(uint8_t addr, uint8_t *data);
inline uint8_t	pcf8574_read		(uint8_t addr, uint8_t *data);
inline uint8_t	pcf8574_setbits		(uint8_t addr, uint8_t bits);
inline uint8_t	pcf8574_clearbits	(uint8_t addr, uint8_t bits);

//uint8_t		pcf8574_genericbits	(uint8_t addr, uint8_t bits, uint8_t op);
uint8_t			pcf8574_genericbits(uint8_t addr, uint8_t ored, uint8_t anded);


inline uint8_t pcf8574_write(uint8_t addr, uint8_t *data)
{
	return i2c_write(PCF8574_ADDR | addr, data, 1) ? 0 : 1;
}

inline uint8_t pcf8574_read(uint8_t addr, uint8_t *data)
{
	return i2c_read(PCF8574_ADDR | addr, data, 1) ? 0 : 1;
}

inline uint8_t pcf8574_setbits(uint8_t addr, uint8_t bits)
{
	return pcf8574_genericbits(addr, bits, 0xFF);
}

inline uint8_t pcf8574_clearbits(uint8_t addr, uint8_t bits)
{
	return pcf8574_genericbits(addr, 0, ~bits);
}

inline uint8_t pcf8574_putbits(uint8_t addr, uint8_t bits, uint8_t mask)
{
	return pcf8574_genericbits(addr, bits & mask, ~mask);
}

#endif

