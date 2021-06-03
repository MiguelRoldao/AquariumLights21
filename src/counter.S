#include <avr/io.h>
#include <counter.h>

#define counter_SREG _SFR_IO_ADDR(SREG)

#define LEDS_PIN_MASK 0b00101111


	
	.section .data

	.extern counter_cnt
	.extern counter_pwm_cnt
	.extern counter_pwm_values

	.section .text


	.global counter_vector
counter_vector:
	push	r24
	in	r24, counter_SREG
	push	r24
	push	r25
	push	r22
	push	r23
	push	ZL
	push	ZH
	
	lds	r24, counter_cnt
	lds	r25, counter_cnt+1
	adiw	r24, 1
	sts	counter_cnt, r24
	sts	counter_cnt+1, r25
	
	in	r23, 
	lds	r24, counter_pwm_cnt
	ldi	r25, 5
	ldi	ZL, lo8(counter_pwm_values)
	ldi	ZH, hi8(counter_pwm_values)
	
	ld	r22, Z+
	cp	r24, r22
	br
	
	
	
	
counter_vector_done:
	inc	r24
	sts	counter_pwm_cnt, r24
	
	pop	ZH
	pop	ZL
	pop	r23
	pop	r22
	pop	r25
	pop	r24
	out	counter_SREG, r24
	pop	r24
	reti
