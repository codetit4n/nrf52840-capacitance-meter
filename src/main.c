#include "board.h"
#include "uarte.h"

#define NRF_P0_BASE 0x50000000UL
#define P0_OUT REG32(NRF_P0_BASE + 0x504)
#define P0_DIR REG32(NRF_P0_BASE + 0x514)

#define PIN 27
#define ADC_PIN 4 // wip

int main(void) {
	init_uarte0();

	P0_DIR |= (1u << PIN);

	while (1) {
		/* Discharge capacitor */
		P0_OUT &= ~(1u << PIN);
		uarte_write("DISCHARGE\r\n", sizeof("DISCHARGE\r\n") - 1);

		delay(6 * 1000 * 1000);

		/* Charge capacitor */
		P0_OUT |= (1u << PIN);
		uarte_write("CHARGE\r\n", sizeof("CHARGE\r\n") - 1);

		delay(6 * 1000 * 1000);
	}
}
