#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define eeprom_setup_write() (EECR = (0 << EEPM1) | (0 << EEPM0))

#define eeprom_ready() (!(EECR & (1 << EEPE)))

#define eeprom_read(address) {EEAR = address;\
							  EECR |= (1 << EERE);\
}
#define eeprom_get_value() (EEDR)

#define eeprom_set_address(address) (EEAR = address)
#define eeprom_set_write_data(data) (EEDR = data)
#define eeprom_begin_write() {EECR |= (1 << EEMPE); EECR |= (1 << EEPE);}


