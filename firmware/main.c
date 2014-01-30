#include "throttle.h"

#define BRAKE PB1
#define THROTTLE_OUT PB0

/*

Throttle in MUST be PB2
Throttle out MUST be PB0
*/


int main(void) {
	set_up_interface(BRAKE);

	return 0;
}