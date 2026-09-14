#include "adc.h"
#include "board.h"

static int16_t sample = 0; // SAADC stores sample as 16 bit two's complement value

void init_saadc0(void) {
	ADC_PSELP_REG = ADC_INPUT;
	ADC_RESOLUTION_REG = 2;
	ADC_CONFIG_REG = (0u << 0) |  // RESP   bits 1:0   -> bypass
			 (0u << 4) |  // RESN   bits 5:4   -> bypass
			 (0u << 8) |  // GAIN   bits 10:8  -> 1/6
			 (0u << 12) | // REFSEL bit 12     -> internal 0.6 V
			 (1u << 16) | // TACQ   bits 18:16 -> 5 us
			 (0u << 20) | // MODE   bit 20     -> single-ended
			 (0u << 24);  // BURST  bit 24     -> disabled

	ADC_EVENTS_DONE_REG = 0;

	ADC_ENABLE_REG = 1; // Enable SAADC
}

uint32_t saadc_read(void) {
	ADC_EVENTS_STARTED_REG = 0;
	ADC_EVENTS_DONE_REG = 0;

	ADC_RESULT_PTR_REG = (uint32_t)&sample;
	ADC_RESULT_MAXCNT_REG = 1;

	ADC_TASKS_START_REG = 1;

	while (ADC_EVENTS_STARTED_REG == 0) {
		// wait until SAADC is ready
	}

	ADC_TASKS_SAMPLE_REG = 1;

	while (ADC_EVENTS_DONE_REG == 0) {
		// wait until sample is stored
	}

	if (sample < 0) {
		sample = 0;
	}

	uint32_t milivolts = sample * 3600 / 4095;
	return milivolts;
}
