#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include <i2c.h>


uint8_t i2c_write(uint8_t addr, uint8_t *data, uint8_t len)
{
	uint8_t i = 0;
	addr <<= 1;
	i2c_start();
	if(!i2c_wbyte(addr))
	{
		while( i<len )
		{
			if(i2c_wbyte(data[i])) break;
			i++;
		}
	}
	i2c_stop();
	_delay_us(100);
	return i;
}

uint8_t i2c_read(uint8_t addr, uint8_t *data, uint8_t len)
{
	uint8_t i = 0;
	addr <<= 1;
	addr |= 0b00000001;
	i2c_start();
	if( (!i2c_wbyte(addr)) && len )
	{
		while( i<(len-1) )
		{
			data[i] = i2c_rbyte(ACK);
			i++;
		}
		data[i] = i2c_rbyte(NACK);
		i++;
	}
	i2c_stop();
	_delay_us(100);
	return i;
}

