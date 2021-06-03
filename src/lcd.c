/*
 * $projectname$.cpp
 *
 * Created: $date$
 * Author : $user$
 */ 
#include <util/delay.h>
#include <stdint.h>
#include <pcf8574.h>
#include <lcd.h>


uint8_t lcd_init()
{
	uint8_t retval = 0;
	_delay_ms(50);
	retval |= lcd_write4(0, 0x3);
	//while(1);
	_delay_ms(5);
	retval |= lcd_write4(0, 0x3);
	_delay_us(125);
	retval |= lcd_write4(0, 0x3);
	retval |= lcd_write4(0, 0x2);

	retval |= lcd_setfunction(0, 1, 0);
	retval |= lcd_power(1, 0, 0);
	retval |= lcd_clear();
	retval |= lcd_entrymode(1, 0);
	return retval;
}



uint8_t lcd_write(uint8_t rs, uint8_t data)
{
	uint8_t retval = 0;
	retval |= lcd_write4(rs, data>>4);
	retval |= lcd_write4(rs, data);
	return retval;
}

uint8_t lcd_read(uint8_t rs, uint8_t *data)
{
	uint8_t retval = 0;
	uint8_t temp;
	retval |= lcd_read4(rs, &temp);
	retval |= lcd_read4(rs, data);
	temp &= 0xF0;
	*data >>= 4;
	*data |= temp;
	
	return retval;
}


uint8_t lcd_isbusy()
{
	uint8_t data;
	lcd_read(0, &data);
	data >>= LCD_P_D7;
	return data;
}

uint8_t lcd_instruction_delay(uint8_t op)
{
	uint8_t retval = lcd_write(0, op);
	_delay_ms(2);
	return retval;
}

inline uint8_t lcd_write_data(uint8_t data)
{
	return lcd_write(1, data);
}









__attribute__ ((weak)) uint8_t lcd_backlight(uint8_t state)
{
	return 0;
}

__attribute__ ((weak)) uint8_t lcd_write4(uint8_t rs, uint8_t data)
{
	return 0;
}

__attribute__ ((weak)) uint8_t lcd_read4(uint8_t rs, uint8_t *data)
{
	return 0;
}






