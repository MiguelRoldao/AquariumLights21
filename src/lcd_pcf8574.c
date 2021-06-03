/*
 * $projectname$.c
 *
 * Created: $date$
 * Author : $user$
 */ 

#include <lcd.h>
#include <pcf8574.h>
#include <stdint.h>
#include <util/delay.h>

uint8_t lcd_backlight(uint8_t state)
{
	uint8_t mask = 1<<LCD_P_BL;
	if(state)
		return pcf8574_setbits(LCD_ADDR, mask);
	else
		return pcf8574_clearbits(LCD_ADDR, mask);
}

uint8_t lcd_write4(uint8_t rs, uint8_t data)
{
	uint8_t out = rs<<LCD_P_RS | data<<LCD_P_D4 | 0<<LCD_P_RW | 1<<LCD_P_E;
	if (pcf8574_putbits(LCD_ADDR, out, 0xF7)) return 1;
	_delay_us(1);
	if (pcf8574_clearbits(LCD_ADDR, 1<<LCD_P_E)) return 2;
	_delay_us(50);
	return 0;
}

/*
uint8_t lcd_read4(uint8_t rs, uint8_t *data)
{
	uint8_t out = rs<<LCD_P_RS | 0xF<<LCD_P_D4 | 1<<LCD_P_E | 1<<LCD_P_RW;
	if (pcf8574_putbits(LCD_ADDR, out, 0xF7)) return 1;
	_delay_us(100);
	if (pcf8574_read(LCD_ADDR, data)) return 2;
	if (pcf8574_clearbits(LCD_ADDR, 1<<LCD_P_E)) return 3;
	_delay_us(100);
	return 0;
}*/

