#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define THROTTLE_IN PB2
#define REGEN_OUT PB1
#define THROTTLE_OUT PB0

#define set_up_input(in) {DDRB &= ~(1 << in); PORTB |= (1 << in);}
#define set_up_output(out) (DDRB |= (1 << THROTTLE_OUT) | (1 << REGEN_OUT) | (1 << out))

#define set_up_adc() {ADMUX |= (1 << MUX0) | (1 << ADLAR); ADCSRA |= (1 << ADPS1) | (1 << ADPS0); ADCSRA |= (1 << ADEN);}

//Inverting mode to prevent blips
#define set_up_timer0() { \
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00) | (1 << WGM01); \
	TCCR0B |= (1 << CS00); \
}

#define set_output_high(out) (PORTB |= (1 << out))
#define set_output_low(out) (PORTB &= ~(1 << out))
#define get_input(in) (PINB & (1 << in))

#define start_adc() (ADCSRA |= (1 << ADSC))
#define adc_is_running() ((ADCSRA & (1 << ADSC)) >> ADSC)
#define adc_get_value() (ADCH)

//Invert because in inverted mode
#define set_timer0_duty_throttle(duty) {OCR0A = 0xFF - (duty);}
#define set_timer0_duty_regen(duty) {OCR0B = 0xFF - (duty);}
#define enable_timer0() (TCCR0B |= (1 << CS00))
#define disable_timer0() (TCCR0B &= ~(1 << CS00))

#define activate_regen(out) {DDRB |= (1 << out); PORTB |= (1 << out);}
#define disable_regen(out) {DDRB |= (1 << out); PORTB &= ~(1 << out);}

#define eeprom_read(address) {EEAR = address;\
							  EECR |= (1 << EERE);\
}
#define eeprom_get_value() (EEDR)
