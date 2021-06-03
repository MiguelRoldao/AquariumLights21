#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

//#include <counter.h>
volatile uint16_t counter_cnt;
volatile uint8_t counter_pwm_cnt;
volatile uint8_t counter_pwm_values[5];

void counter_init() {


	TCCR1A = 0;
	TCCR1B = 1<<3 | 4<<0;		// 256 prescaler
	TCCR1C = 0;
	OCR1A = 15624;		// 1 second
	TIMSK1 = 1<<1;
	
	counter_cnt = 0;
}

ISR(TIM0_COMPA_vect)
{

	//PINA = 1;
}
