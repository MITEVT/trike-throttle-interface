#include "throttle.h"

#define SW_IN PB4
#define SW_OUT PB3


/*

Throttle in MUST be PB2
Throttle out MUST be PB0
Regen out must be PB1
*/

/*******************
* Functionality:
* PWM Signal outputed relative to throttle input.
* When Reverse switch brought low, signal is passed to motor controller and output switched to regen, after delay 
********************/

/*******************
State Machine Spec

St|In|St'
T |0 |R
T |1 |T
R |0 |R
R |1 |T

*********************/


typedef void *(*StateFunction)(void);

void *regenerativeBraking(void);
void *throttle(void);

uint16_t read_throttle(void) {
	start_adc();
	while(adc_is_running()) {

	}
	return adc_get_value();
}

void *throttle(void) {
	uint16_t throttleIn = read_throttle();
	if (get_input(SW_IN)) {
		set_timer0_duty_Regen(0);
		set_timer0_duty_Throttle(throttleIn);
		return throttle;
	} else {
		set_timer0_duty_Regen(0);
		set_timer0_duty_Throttle(0);
		_delay_ms(50);
		activate_regen(SW_OUT);
		_delay_ms(50);
		return regenerativeBraking;
	}
}

void *regenerativeBraking(void) {
	uint16_t throttleIn = read_throttle();
	if (!get_input(SW_IN)) {
		set_timer0_duty_Regen(throttleIn);
		set_timer0_duty_Throttle(0);
		return regenerativeBraking;
	} else {
		set_timer0_duty_Regen(0);
		set_timer0_duty_Throttle(0);
		_delay_ms(50);
		disable_regen(SW_OUT);
		_delay_ms(50);
		return throttle;
	}
}

void setup(void) {
	set_up_input(SW_IN);
	set_up_output(SW_OUT);

	set_up_adc();
	set_up_timer0();

	set_timer0_duty_Throttle(0);
	set_timer0_duty_Regen(0);
}

int main(void) {
	setup();
	
	StateFunction stateFunc = throttle;

	while(1) {
		stateFunc = (StateFunction)(*stateFunc)();
		_delay_ms(10);
	}
}