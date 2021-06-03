TARGET	= led_on
SRCS	= main.c src/*.c src/*.S
LIBS	= inc


MCU_GCC		= attiny84a
MCU_DUDE	= t84
F_CPU		= 8000000

CC			= avr-gcc
CFLAGS		= -std=c99 -Wall -g -mmcu=${MCU_GCC} -DF_CPU=${F_CPU} -I. -Os

DUDE		= avrdude
DFLAGS		= -d -m avr
PROGRAMMER	= usbasp
F_PROG		= 125kHz
PORT		= usb

OBJCOPY		= avr-objcopy
OBJDUMP		= avr-objdump

SIZE		= avr-size
SFLAGS		= -C




all:
	${CC} ${CFLAGS} -o ${TARGET}.elf ${SRCS} -I ${LIBS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.elf ${TARGET}.hex
	$(SIZE) $(SFLAGS) --mcu=$(MCU_GCC) $(TARGET).elf

flash:
	$(DUDE) -p ${MCU_DUDE} -c $(PROGRAMMER) -B $(F_PROG) -U flash:w:${TARGET}.hex:i -P $(PORT) -v -v

dump:
	$(OBJDUMP) $(DFLAGS) $(TARGET).elf

mem:
	$(SIZE) $(SFLAGS) --mcu=$(MCU_GCC) $(TARGET).elf
	@echo "\nData memory usage:"
	@$(OBJDUMP) -t led_on.elf | egrep 'O \.(bss|data)' | sort
	@echo "\nProgram memory usage:"
	@$(OBJDUMP) -t led_on.elf | egrep 'O \.(text)' | sort

clean:
	rm -f *.elf *.hex
