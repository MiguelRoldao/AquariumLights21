
#ifndef _I2C_LIB_H
#define _I2C_LIB_H


#define	SDA		6		// SDA pin number
#define	SCL		4		// SCL pin number
#define	SDA_PORT	PORTA		// SDA pin port
#define	SCL_PORT	PORTA		// SCL pin port

#define ACK	0
#define NACK	1

#ifdef __ASSEMBLER__

#define SDA_OUT		_SFR_IO_ADDR(SDA_PORT)
#define SCL_OUT		_SFR_IO_ADDR(SCL_PORT)
#define SDA_DIR		(_SFR_IO_ADDR(SDA_PORT) - 1)
#define SCL_DIR		(_SFR_IO_ADDR(SCL_PORT) - 1)
#define SDA_IN		(_SFR_IO_ADDR(SDA_PORT) - 2)
#define SCL_IN		(_SFR_IO_ADDR(SCL_PORT) - 2)

#else //!ASSEMBLER

#include <stdint.h>


// ADDR is ALWAYS 7-bit (no r/w bit)
uint8_t			i2c_write	(uint8_t addr, uint8_t *data, uint8_t len);
uint8_t			i2c_read	(uint8_t addr, uint8_t *data, uint8_t len);

extern void		i2c_start	(void);
extern void		i2c_stop	(void);
// returns 0 - if acknowledged
extern uint8_t		i2c_wbyte	(uint8_t data);
// returns data read
extern uint8_t		i2c_rbyte	(uint8_t ack);

#endif //ASSEMBLER

#endif
