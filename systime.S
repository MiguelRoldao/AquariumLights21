#include <avr/io.h>

	.section .data
	.global systime_s
	.global systime_m
	.global systime_h
systime_s:
	.byte 1
systime_m:
	.byte 1
systime_h:
	.byte 1

	.section .text

	.global	TIM1_COMPA_vect
TIM1_COMPA_vect:
vector_systime:
	push	ZL
	push	ZH
	push	r24
	push	r25
	push	r26
	push	r27
	push	r1
	in	r1, SREG
	push	r1
	clr	r1

	ldi	ZL, LOW(_dt)
	ldi	ZH, HIGH(_dt)
	ld	r24, Z+
	ld	r25, Z+
	ld	r26, Z+
	inc	r24
	adc	r25, r1
	adc	r26, r1
	sbiw	Z, 3

	cpi	r24, 0x80
	brne	_vector_systime_st
	cpi	r25, 0x51
	brne	_vector_systime_st
	cpi	r26, 0x01
	brne	_vector_systime_st

	st	Z+, r1
	st	Z+, r1
	st	Z+, r1
	rjmp	_vector_systime_end

_vector_systime_st:
	st	Z+, r24
	st	Z+, r25
	st	Z+, r26

_vector_systime_end:
	ldi	r24, 1
	out	PINA, r24

	pop	r1
	out	SREG, r1
	pop	r1
	pop	r27
	pop	r26
	pop	r25
	pop	r24
	pop	ZH
	pop	ZL
	reti
