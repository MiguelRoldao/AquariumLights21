
#include <avr/io.h>
#include <i2c.h>


	.section .text
	
	.global	i2c_start
i2c_start:
	cbi	SDA_DIR, SDA
	cbi	SCL_DIR, SCL
	cbi	SDA_OUT, SDA
	cbi	SCL_OUT, SCL
	
	rcall	i2c_delay
	sbi	SDA_DIR, SDA			; low SDA
	rcall	i2c_halfdelay
	sbi	SCL_DIR, SCL			; low SCL
	rcall	i2c_halfdelay
	
	ret



	.global	i2c_stop
i2c_stop:
	sbi	SDA_DIR, SDA			; low SDA
	rcall	i2c_halfdelay
	cbi	SCL_DIR, SCL			; high SCL
i2c_stop_loop:
	sbis	SDA_IN, SCL
	rjmp	i2c_stop_loop			; clock stretching
	rcall	i2c_halfdelay
	cbi	SDA_DIR, SDA			; high SDA
	rcall	i2c_delay
	ret



	.global	i2c_wbyte
i2c_wbyte:
	sec
	rol	r24
	rjmp	i2c_wbyte_out
i2c_wbyte_loop:
	lsl	r24
	breq	i2c_wbyte_ack
i2c_wbyte_out:
	brcs	i2c_wbyte_out1
i2c_wbyte_out0:
	sbi	SDA_DIR, SDA			; low SDA
	rjmp	i2c_wbyte_outdone
i2c_wbyte_out1:
	cbi	SDA_DIR, SDA			; high SDA
i2c_wbyte_outdone:
	rcall	i2c_halfdelay
	cbi	SCL_DIR, SCL			; high SCL
	rcall	i2c_delay
	sbi	SCL_DIR, SCL			; low SCL
	rcall	i2c_halfdelay
	rjmp	i2c_wbyte_loop

i2c_wbyte_ack:
	cbi	SDA_DIR, SDA			; high SDA
	rcall	i2c_halfdelay
	cbi	SCL_DIR, SCL			; high SCL
	rcall	i2c_halfdelay
i2c_wbyte_ackwait:
	sbis	SCL_IN, SCL			; wait for slave to release SCL
	rjmp	i2c_wbyte_ackwait
	rcall	i2c_halfdelay
	
	clr	r24
	clr	r25
	sbic	SDA_IN, SDA
	ldi	r24, 1
	
	rcall	i2c_halfdelay
	sbi	SCL_DIR, SCL			; low SCL
	rcall	i2c_halfdelay
	ret



	.global	i2c_rbyte
i2c_rbyte:
	push	r24
	
	clr	r24				; read byte to this register
	ldi	r25, 8				; iterator
i2c_rbyte_loop:
	rcall	i2c_halfdelay
	cbi	SCL_DIR, SCL			; high SCL
	rcall	i2c_halfdelay
	lsl	r24
	sbic	SDA_IN, SDA
	ori	r24, 0b00000001
	rcall	i2c_halfdelay
	sbi	SCL_DIR, SCL			; low SCL
	rcall	i2c_halfdelay
	dec	r25
	brne	i2c_rbyte_loop
	
	pop	r25
	cpi	r25, 0
	brne	i2c_rbyte_nack
	sbi	SDA_DIR, SDA			; low SDA
i2c_rbyte_nack:
	rcall	i2c_halfdelay
	cbi	SCL_DIR, SCL			; high SCL
	rcall	i2c_delay
	sbi	SCL_DIR, SCL			; low SCL
	rcall	i2c_halfdelay
	cbi	SDA_DIR, SDA			; high SDA
	clr	r25
	ret




; wastes 38 clk cycles
i2c_delay:
	push	r24
	ldi	r24, 0x09 ;60
i2c_delay_loop:
	dec	r24
	brne	i2c_delay_loop
	pop	r24
	ret
	
	

; wastes 19 clk cycles
i2c_halfdelay:
	push	r24
	ldi	r24, 0x03 ;28
i2c_halfdelay_loop:
	dec	r24
	brne	i2c_halfdelay_loop
	pop	r24
	nop
	ret

