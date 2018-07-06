/*
 * xmega_utils.c
 *
 */

#include <avr/io.h>
#include "xmega.h"

int main(void)
{
	// NVM test
	CCPWrite(&PMIC.CTRL, 0x55);
    GPIO0 = NVM_read_user_signature_byte(0);

	// EEPROM test
	NVM_eeprom_erase_all();

	// NVM I/O mode not available on E5 range
/*
	uint8_t buffer[32] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
						  17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
	NVM_eeprom_load_buffer(buffer, sizeof(buffer));
*/

	EEP_EnableMapping();
	NVM_eeprom_erase_write_buffer();
	uint8_t *ptr = (uint8_t *)EEP_MAPPED_ADDR(2, 0);
	for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
		*ptr++ = i;

	NVM_eeprom_atomic_write_page(2);

    while (1)
    {
    }
}

