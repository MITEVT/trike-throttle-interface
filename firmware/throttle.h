#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define THROTTLE_IN PB2
#define THROTTLE_OUT PB0

#define set_up_input(in) {}
#define set_up_output() (DDRB |= (1 << THROTTLE_OUT))

#define set_up_adc() {ADMUX |= (1 << MUX0) | (1 << ADLAR); ADCSRA |= (1 << ADPS1) | (1 << ADPS0); ADCSRA |= (1 << ADEN);}

//Inverting mode to prevent blips
#define set_up_timer0() { \
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM00) | (1 << WGM01); \
	TCCR0B |= (1 << CS00); \
}

//Clear on OCR1C, Start timer, 
#define set_up_timer1() { \
	TCCR1 |= (1 << CTC1) | (1 << CS10); \
	PLLCSR |= (1 << PLLE); \
	_delay_us(100); \
	while(!(PLLCSR & (1 << PLOCK))) {} \
	PLLCSR |= (1 << PCKE); \
}

#define set_output_high(out) (PORTB |= (1 << out))
#define set_output_low(out) (PORTB &= ~(1 << out))
#define get_input(in) (PINB & (1 << in))

#define start_adc() (ADCSRA |= (1 << ADSC))
#define adc_is_running() ((ADCSRA & (1 << ADSC)) >> ADSC)
#define adc_get_value() (ADCH)

//Invert because in inverted mode
#define set_timer0_duty(duty) {OCR0A = 0xFF - (duty * 255 / 100);}
#define enable_timer0() (TCCR0B |= (1 << CS00))
#define disable_timer0() (TCCR0B &= ~(1 << CS00))

#define set_timer1_overflow(ovf) {OCR1B = ovf; OCR1C = ovf;}
#define enable_timer1_interrupt() (TIMSK |= (1 << OCIE1B))
#define disable_timer1_interrupt() (TIMSK &= ~(1 << OCIE1B))

void set_up_interface(uint8_t brakeIn);
void start_interface(void);
void stop_interface(void);

