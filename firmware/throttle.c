#include "throttle.h"

#define thIn PB2
#define thOut PB0

uint8_t bIn;

void set_up_interface(uint8_t brakeIn) {
	bIn = brakeIn;

	set_up_input(bIn);
	set_up_output();
	set_up_adc();
	set_up_timer0();

	set_duty(0);
}

uint16_t read_throttle(void) {
	start_adc();
	while(adc_is_running()) {

	}
	return adc_get_value();
}

void start_interface(void) {
	while (1) {
		uint16_t throttle = read_throttle();
		uint8_t brake = get_input(bIn);

		if (!brake) {
			set_duty(throttle * 100 / 256);
		} else {
			set_duty(0);
			_delay_ms(100);
			set_duty(throttle * 100 / 256);
		} 
	}
}

void stop_interface(void) {
	set_duty(0);
}



