/*
 * $projectname$.c
 *
 * Created: $date$
 * Author : $user$
 */ 

#ifndef	_MIRO_LCD_H
#define	_MIRO_LCD_H


#include <stdint.h>

#define LCD_ADDR	0x7

#define LCD_P_RS	0
#define	LCD_P_RW	1
#define	LCD_P_E		2
#define LCD_P_BL	3
#define LCD_P_D4	4
#define LCD_P_D5	5
#define LCD_P_D6	6
#define LCD_P_D7	7

#define LCD_BL_ON	1
#define	LCD_BL_OFF	0


// Define these 3 functions externally
uint8_t lcd_backlight(uint8_t state);
uint8_t lcd_write4(uint8_t rs, uint8_t data);
uint8_t lcd_read4(uint8_t rs, uint8_t *data);




uint8_t lcd_init(); //uint8_t lcd_init(uint8_t id, uint8_t s, uint8_t n, uint8_t f);
uint8_t lcd_write(uint8_t rs, uint8_t data);
uint8_t lcd_read(uint8_t rs, uint8_t *data);
inline uint8_t lcd_writecmd(uint8_t cmd);
inline uint8_t lcd_writedata(uint8_t data);

uint8_t lcd_isbusy(void);
uint8_t lcd_instruction_delay(uint8_t op);
inline uint8_t lcd_clear(void);
inline uint8_t lcd_home(void);
inline uint8_t lcd_entrymode(uint8_t id, uint8_t s);
inline uint8_t lcd_power(uint8_t d, uint8_t c, uint8_t b);
inline uint8_t lcd_shift(uint8_t sc, uint8_t rl);
inline uint8_t lcd_setfunction(uint8_t dl, uint8_t n, uint8_t f);
inline uint8_t lcd_cgram_addr(uint8_t addr);
inline uint8_t lcd_ddram_addr(uint8_t addr);
inline uint8_t lcd_instruction(uint8_t op);



inline uint8_t lcd_writecmd(uint8_t cmd)
{
	return lcd_write(0, cmd);
}

inline uint8_t lcd_writedata(uint8_t data)
{
	return lcd_write(1, data);
}

inline uint8_t lcd_clear(void)
{
	return lcd_instruction_delay(0x01);
}

inline uint8_t lcd_home(void)
{
	return lcd_instruction_delay(0x02);
}

inline uint8_t lcd_entrymode(uint8_t id, uint8_t s)
{
	id &= 1;
	s &= 1;
	return lcd_instruction(0x04 | id<<1 | s<<0);
}

inline uint8_t lcd_power(uint8_t d, uint8_t c, uint8_t b)
{
	d &= 1;
	c &= 1;
	b &= 1;
	return lcd_instruction(0x08 | d<<2 | c<<1 | b<<0);
}

inline uint8_t lcd_shift(uint8_t sc, uint8_t rl)
{
	sc &= 1;
	rl &= 1;
	return lcd_instruction(0x10 | sc<<3 | rl<<2);
}

inline uint8_t lcd_setfunction(uint8_t dl, uint8_t n, uint8_t f)
{
	dl &= 1;
	n &= 1;
	f &= 1;
	return lcd_instruction(0x20 | dl<<4 | n<<3 | f<<2);
}

inline uint8_t lcd_cgram_addr(uint8_t addr)
{
	addr &= 0x3F;
	return lcd_instruction(0x40 | addr);
}

inline uint8_t lcd_ddram_addr(uint8_t addr)
{
	addr &= 0x7F;
	return lcd_instruction(0x80 | addr);
}

inline uint8_t lcd_instruction(uint8_t op)
{
	return lcd_write(0, op);
}


#endif
