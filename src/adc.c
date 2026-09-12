#include "adc.h"
#include "board.h"

static int16_t sample = 0; // SAADC stores sample as 16 bit two's complement value

void init_saadc0(void) {
	PSELP = ADC_INPUT;
	RESOLUTION = 2;
	CONFIG = (0u << 0) |  // RESP   bits 1:0   -> bypass
		 (0u << 4) |  // RESN   bits 5:4   -> bypass
		 (0u << 8) |  // GAIN   bits 10:8  -> 1/6
		 (0u << 12) | // REFSEL bit 12     -> internal 0.6 V
		 (1u << 16) | // TACQ   bits 18:16 -> 5 us
		 (0u << 20) | // MODE   bit 20     -> single-ended
		 (0u << 24);  // BURST  bit 24     -> disabled

	EVENTS_DONE = 0;

	ENABLE = 1; // Enable SAADC
}

uint32_t saadc_read(void) {
	EVENTS_STARTED = 0;
	EVENTS_DONE = 0;

	RESULT_PTR = (uint32_t)&sample;
	RESULT_MAXCNT = 1;

	TASKS_START = 1;

	while (EVENTS_STARTED == 0) {
		// wait until SAADC is ready
	}

	TASKS_SAMPLE = 1;

	while (EVENTS_DONE == 0) {
		// wait until sample is stored
	}

	if (sample < 0) {
		sample = 0;
	}

	uint32_t milivolts = sample * 3600 / 4095;
	return milivolts;
}
