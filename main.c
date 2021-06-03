#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include <systime.h>
#include <i2c.h>
#include <pcf8574.h>
#include <lcd.h>

#define DEBUG 2

uint8_t data = 0b11101111;
uint8_t data1 = 0b11111111;
uint8_t data2 = 0b00000000;

int main(int argc, char const *argv[])
{
	CLKPR = 1<<7;
	CLKPR = 0;

	DDRA |= 0b00000001;	// pin is output

	systime_init();

	sei();
	

	
#if DEBUG == 2
	if(lcd_init(1, 0, 1, 0))
	{
		PORTA |= 0b00000001; 	// output high
		while(1);
	}
	
	/*if(lcd_clear())
	{
		PORTA |= 0b00000001; 	// output high
		while(1);
	}*/
	lcd_write(1, 'A');
	lcd_backlight(1);
	while(1);
	if(pcf8574_read(0, &data1) != 0)
	{
		PORTA |= 0b00000001; 	// output high
		while(1);
	}
	while(1)
	{
		pcf8574_read(0, &data1);
		if (data1 == data)
		{
			PORTA |= 0b00000001; 	// output high
			lcd_backlight(LCD_BL_OFF);
		}
		else
		{
			PORTA &= 0b11111110; 	// output high
			lcd_backlight(LCD_BL_ON);
		}
	}
	
#elif DEBUG == 1
	while(1)
	{
		if(i2c_write(0x40, &data, 1) == 1)
		{
			PORTA |= 0b00000001; 	// output high
		}
		_delay_ms(1000);
		if(i2c_write(0x40, &data1, 1) == 1)
		{
			PORTA &= 0b11111110; 	// output high
		}
		_delay_ms(1000);
	}
#endif

	return 0;
}
