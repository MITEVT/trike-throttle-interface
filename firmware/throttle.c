#include "throttle.h"

#define thIn PB2
#define thOut PB0

uint8_t rIn;
uint8_t inRegen;
uint8_t bOut;

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
		if (inRegen) {
			inRegen = 0;
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(0);
			_delay_ms(500);
			disable_regen(bOut);
			_delay_ms(500);
		}
		set_timer0_duty_Regen(0);
		set_timer0_duty_Throttle(throttle);
	} else {
		if (!inRegen) {
			inRegen = 1;
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(0);
			_delay_ms(500);
			activate_regen(bOut);
			_delay_ms(500);
		}
		set_timer0_duty_Throttle(0);
		set_timer0_duty_Regen(throttle);
	}
}

void set_up_interface(uint8_t regenIn, uint8_t brakeOut) {
	rIn = regenIn;
	bOut = brakeOut;
	inRegen = 0;

	set_up_input(rIn);
	set_up_output(bOut);
	set_up_adc();
	set_up_timer0();
	set_up_timer1();
	set_timer1_overflow(100);

	sei();

	set_timer0_duty_Throttle(0);
	set_timer0_duty_Regen(0);
	disable_regen(bOut);
}

void start_interface(void) {
	enable_timer1_interrupt();
}

void stop_interface(void) {
	disable_timer1_interrupt();
}



