#include <avr/io.h>
#include <util/delay.h>


#define BRAKE_IN 
#define THROTTLE_IN PB2
#define THROTTLE_OUT PB0

#define set_up_input(in) {}
#define set_up_output() (DDRB |= (1 << THROTTLE_OUT))

#define set_up_adc() {ADMUX |= (1 << MUX0) | (1 << ADLAR); ADCSRA |= (1 << ADPS1) | (1 << ADPS0); ADCSRA |= (1 << ADEN);}

#define set_up_timer0() { \
	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); \
	TCCR0B |= (1 << CS00); \
	TIMSK |= (1 << TOIE0); \
}

#define set_output_high(out) (PORTB |= (1 << out))
#define set_output_low(out) (PORTB &= ~(1 << out))
#define get_input(in) (PINB & (1 << in))

#define start_adc() (ADCSRA |= (1 << ADSC))
#define adc_is_running() ((ADCSRA & (1 << ADSC)) >> ADSC)
#define adc_get_value() (ADCH)

#define set_duty(duty) {OCR0A = duty * 255 / 100;}


void set_up_interface(uint8_t brakeIn);

