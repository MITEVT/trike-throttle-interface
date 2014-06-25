# Trike-Throttle Interface
	Interface between the throttle and BMS for the NY Tricycle Project
### Instructions for Use
	1. Use throttle profile python program (either) to come up with a throttle and regen profile
		- Throttle profile consists of 256 integers with values between 0 and 255
		- Old profile program parameters can be edited in main.py (Hint: giving the round parameter a non-zero value will give you a nicely formatted integer array)
	2. Enter throttle and regen profiles into eeprom loader program by replacing the values in the arrays at the top of main.c in eeprom loader folder
	3. Program attiny with eeprom loader program and give it a good amount of time for it to run
	4. Program attiny with throttle interface program
	5. Test
	6. Rinse and repeat
