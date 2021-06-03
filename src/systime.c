#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include <systime.h>

void systime_init() {
	_dt = 0;

	TCCR1A = 0;
	TCCR1B = 1<<3 | 4<<0;		// 256 prescaler
	TCCR1C = 0;
	OCR1A = 15624;		// 1 second
	TIMSK1 = 1<<1;
}

ISR(TIM1_COMPA_vect)
{
	uint32_t t = _dt + 1;
	if (t >= ONE_DAY) t -= ONE_DAY;
	_dt = t;
	//PINA = 1;
}
