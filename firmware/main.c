#include "throttle.h"

#define SW_IN PB4
#define SW_OUT PB3

#define SWITCH_DELAY 50


/*

Throttle in MUST be PB2
Throttle out MUST be PB0
Regen out must be PB1
*/

/*******************
* Functionality:
* PWM output relative to throttle input.
* When regen switch (BRAKE-SW on Kelley) brought low, signal is passed to motor controller and throttle output
* switched to PB1, after a short delay.
********************/

/*******************
*State Machine Spec
*
*St|In|St'
*T |0 |R
*T |1 |T
*R |0 |R
*R |1 |T
*
*********************/


typedef void *(*StateFunction)(void);

void *regenerativeBraking(void);
void *throttle(void);

uint8_t read_eeprom(uint16_t address) {
	eeprom_read(address);
	return eeprom_get_value();
}

uint16_t read_throttle(void) {
	start_adc();
	while(adc_is_running()) {

	}
	return adc_get_value();
}

void *throttle(void) {
	uint16_t throttleIn = read_throttle();
	uint8_t outputVal = read_eeprom(throttleIn & 0x00FF);
	if (get_input(SW_IN)) {
		set_timer0_duty_regen(0);
		set_timer0_duty_throttle(outputVal);
		return throttle;
	} else {
		set_timer0_duty_regen(0);
		set_timer0_duty_throttle(0);
		_delay_ms(SWITCH_DELAY);
		activate_regen(SW_OUT);
		_delay_ms(SWITCH_DELAY);
		return regenerativeBraking;
	}
}

void *regenerativeBraking(void) {
	uint16_t throttleIn = read_throttle();
	uint8_t outputVal = read_eeprom((throttleIn & 0x00FF) | 0x0100);
	if (!get_input(SW_IN)) {
		set_timer0_duty_regen(outputVal);
		set_timer0_duty_throttle(0);
		return regenerativeBraking;
	} else {
		set_timer0_duty_regen(0);
		set_timer0_duty_throttle(0);
		_delay_ms(SWITCH_DELAY);
		disable_regen(SW_OUT);
		_delay_ms(SWITCH_DELAY);
		return throttle;
	}
}

void setup(void) {
	set_up_input(SW_IN);
	set_up_output(SW_OUT);

	set_up_adc();
	set_up_timer0();

	set_timer0_duty_throttle(0);
	set_timer0_duty_regen(0);
}

int main(void) {
	setup();

	StateFunction stateFunc = throttle;

	while(1) {
		stateFunc = (StateFunction)(*stateFunc)();
		_delay_ms(10);
	}
}