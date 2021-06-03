
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ENCODER_L_PORT	PORTB
#define ENCODER_R_PORT	PORTB
#define ENCODER_L_PIN	PB0
#define ENCODER_R_PIN	PB1

uint8_t encoder_state;
int8_t encoder_steps;

void encoder_init()
{
	// Set pins dependent on port and pin

	GIMSK |= 1<<PCIE1;
	PCMSK1 |= 1<<ENCODER_L_PIN;
	DDRB &= ~(1<<ENCODER_L_PIN);

	GIMSK |= 1<<PCIE1;
	PCMSK1 |= 1<<ENCODER_R_PIN;
	DDRB &= ~(1<<ENCODER_R_PIN);

	
	encoder_state = 0;
	encoder_steps = 0;
	encoder_state = (ENCODER_L_PORT & (1<<ENCODER_L_PIN)) ? 1 : 0;
}






int8_t encoder_getSteps()
{
	int8_t turns;
	cli();
	turns = encoder_steps;
	encoder_steps = 0;
	sei();
	return turns;
}

void encoder_isr()
{
	uint8_t pin_l;
	uint8_t pin_r;
	pin_l = (ENCODER_L_PORT & (1<<ENCODER_L_PIN)) ? 1 : 0;
	pin_r = (ENCODER_R_PORT & (1<<ENCODER_R_PIN)) ? 1 : 0;
	
	if (pin_l == pin_r)
		encoder_state = pin_l;
	else
		encoder_steps += (pin_l == encoder_state) ? 1 : -1;
}


