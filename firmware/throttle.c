#include "throttle.h"

#define thIn PB2
#define thOut PB0

uint8_t rIn;
uint8_t inRegen;

uint16_t read_throttle(void) {
	start_adc();
	while(adc_is_running()) {

	}
	return adc_get_value();
}

ISR(TIM1_COMPB_vect) {
	uint16_t throttle = read_throttle();
	uint8_t input = get_input(rIn);

	if (input) {
		inRegen = 0;
		set_timer0_duty(throttle * 100 / 256);
	} else {
		if (!inRegen) {
			inRegen = 1;
			set_timer0_duty(0);
			_delay_ms(1000);
			
		}
		set_timer0_duty(throttle * 100 / 256);
	}
}

void set_up_interface(uint8_t regenIn) {
	rIn = regenIn;
	inRegen = 0;

	set_up_input(rIn);
	set_up_output();
	set_up_adc();
	set_up_timer0();
	set_up_timer1();
	set_timer1_overflow(100);

	sei();

	set_timer0_duty(0);
}

void start_interface(void) {
	enable_timer1_interrupt();
	//set_timer0_duty(50);
}

void stop_interface(void) {
	disable_timer1_interrupt();
}



