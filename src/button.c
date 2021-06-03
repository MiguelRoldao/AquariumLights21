#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t button_state;
int8_t button_steps;


void button_init()
{
	// any logical change triggers isr
	MCUCR |= 1<<ISC00;
	GIMSK |= 1<<INT0;
	DDRB &= ~(1<<PB2);
	
	button_state = 0;
	button_steps = 0;

}




int8_t button_getSteps()
{
	int8_t turns;
	cli();
	turns = button_steps;
	button_steps = 0;
	sei();
	return turns;
}

void button_isr()
{
	uint8_t pin = (PORTB & (1<<PB2)) ? 1 : 0;
	if (pin)
	{
		
	}
	else
	{
		//button_time = get_ms();
	}
}

