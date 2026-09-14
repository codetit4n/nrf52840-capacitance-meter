#include "adc.h"
#include "board.h"
#include "gpio.h"
#include "timer.h"
#include "uarte.h"
#include "utils.h"

int main(void) {
	init_uarte0();
	init_saadc0();
	init_timer0();

	set_pin_output(PIN);

	while (1) {
		/* Discharge capacitor */
		set_pin_low(PIN);
		uarte_write("CAPACITOR: DISCHARGING\r\n", sizeof("CAPACITOR: DISCHARGING\r\n") - 1);
		uint32_t mV = 0;
		do {
			mV = saadc_read();
		} while (mV > DISCHARGE_THRESHOLD_MV);
		log_volts(mV);

		start_timer();

		/* Charge capacitor */
		set_pin_high(PIN);
		uarte_write("CAPACITOR: CHARGING\r\n", sizeof("CAPACITOR: CHARGING\r\n") - 1);
		mV = 0;
		do {
			mV = saadc_read();
		} while (mV < CHARGE_THRESHOLD_MV);
		log_volts(mV);

		stop_timer();

		uint32_t et = read_ctr();
		log_elapsed_time(et);

		uint32_t nF = (et * 1000) / 10030;
		log_capacitance_nF(nF);

		uint32_t uF_int = nF / 1000;
		uint32_t uF_frac = nF % 1000;
		uint8_t uF_hundreds = uF_frac / 100;
		uint8_t uF_tens = (uF_frac / 10) % 10;
		uint8_t uF_ones = uF_frac % 10;

		log_capacitance_uF(uF_int, uF_hundreds, uF_tens, uF_ones);

		log_br();
	}
}
