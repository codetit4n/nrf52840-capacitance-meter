#include "adc.h"
#include "board.h"
#include "gpio.h"
#include "uarte.h"
#include "utils.h"

int main(void) {
	init_uarte0();
	init_saadc0();

	set_pin_output(PIN);

	while (1) {
		/* Discharge capacitor */
		set_pin_low(PIN);
		uarte_write("DISCHARGE\r\n", sizeof("DISCHARGE\r\n") - 1);
		uint32_t mV = 0;
		do {
			mV = saadc_read();
		} while (mV > DISCHARGE_THRESHOLD_MV);

		log_volts(mV);

		/* Charge capacitor */
		set_pin_high(PIN);
		uarte_write("CHARGE\r\n", sizeof("CHARGE\r\n") - 1);
		mV = 0;
		do {
			mV = saadc_read();
		} while (mV < CHARGE_THRESHOLD_MV);

		log_volts(mV);
	}
}
