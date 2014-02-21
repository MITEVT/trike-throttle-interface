#include "throttle.h"

uint8_t sIn;
uint8_t inRegen;
uint8_t moving;
uint8_t sOut;
uint8_t count;

uint16_t read_throttle(void) {
	start_adc();
	while(adc_is_running()) {

	}
	return adc_get_value();
}

void delayMicroseconds(unsigned int us)
{
        uint8_t oldSREG;

        // calling avrlib's delay_us() function with low values (e.g. 1 or
        // 2 microseconds) gives delays longer than desired.
        //delay_us(us);

        // for the 8 MHz internal clock on the ATmega168

        // for a one- or two-microsecond delay, simply return.  the overhead of
        // the function calls takes more than two microseconds.  can't just
        // subtract two, since us is unsigned; we'd overflow.
        if (--us == 0)
                return;
        if (--us == 0)
                return;

        // the following loop takes half of a microsecond (4 cycles)
        // per iteration, so execute it twice for each microsecond of
        // delay requested.
        us <<= 1;
    
        // partially compensate for the time taken by the preceeding commands.
        // we can't subtract any more than this or we'd overflow w/ small delays.
        us--;

        // disable interrupts, otherwise the timer 0 overflow interrupt that
        // tracks milliseconds will make us delay longer than we want.
        oldSREG = SREG;
        cli();

        // busy wait
        __asm__ __volatile__ (
                "1: sbiw %0,1" "\n\t" // 2 cycles
                "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
        );

        // reenable interrupts.
        SREG = oldSREG;
}

//Divide by 8 because ATtiny actually runs at 1 MHz
void delayMilliseconds(unsigned int ms) {
	unsigned int i;
	for (i = 0; i < ms/8; i++) {
		delayMicroseconds(1000);
	}
}

ISR(TIM1_COMPB_vect) {
	uint16_t throttle = read_throttle();
	uint8_t input = get_input(sIn);

	if (!moving && throttle) {
		if (count++ > 250) {
			moving = 1;
			count = 0;
		}
		if (inRegen) {
			set_timer0_duty_Throttle(0);
			set_timer0_duty_Regen(throttle);
		} else {	
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(throttle);
		}
	} else if (input) {
		if (inRegen) {
			inRegen = 0;
			moving = 0;
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(0);
			delayMilliseconds(1000); //Still bad practice but don't need interrupts during this period anyways, not evne for timer 0
			disable_regen(sOut);
			delayMilliseconds(1000);
		} else {
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(throttle);
		}
	} else {
		if (!inRegen) {
			inRegen = 1;
			moving = 0; //Doesn't hurt if it is actually moving, but helps if it isn't
			set_timer0_duty_Regen(0);
			set_timer0_duty_Throttle(0);
			delayMilliseconds(1000);
			activate_regen(sOut);
			delayMilliseconds(1000);
		} else {
			set_timer0_duty_Throttle(0);
			set_timer0_duty_Regen(throttle);
		}
	}
}

void set_up_interface(uint8_t switchIn, uint8_t switchOut) {
	sIn = switchIn;
	sOut = switchOut;
	inRegen = 0;
	moving = 0;

	set_up_input(sIn);
	set_up_output(sOut);
	set_up_adc();
	set_up_timer0();
	set_up_timer1();
	set_timer1_overflow(100);

	sei();

	set_timer0_duty_Throttle(0);
	set_timer0_duty_Regen(0);
	disable_regen(sOut);
}

void start_interface(void) {
	enable_timer1_interrupt();
}

void stop_interface(void) {
	disable_timer1_interrupt();
}



