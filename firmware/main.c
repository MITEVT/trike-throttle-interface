#include "throttle.h"

#define REGEN PB4
#define BRAKE_OUT PB3

/*

Throttle in MUST be PB2
Throttle out MUST be PB0
*/

/*******************
* Functionality:
* PWM Signal outputed relative to throttle input.
* When Reverse switch brough low, 
********************/


int main(void) {
	set_up_interface(REGEN, BRAKE_OUT);
	start_interface();

	while(1) {

	}

	stop_interface();
	return 0;
}