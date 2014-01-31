#include "throttle.h"

#define REGEN PB1

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
	set_up_interface(REGEN);
	start_interface();

	while(1) {

	}

	return 0;
}