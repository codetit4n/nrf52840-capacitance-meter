#include "board.h"
#include "uarte.h"

#define NRF_P0_BASE 0x50000000UL
#define P0_OUT REG32(NRF_P0_BASE + 0x504)
#define P0_DIR REG32(NRF_P0_BASE + 0x514)

#define PIN 27
#define ADC_INPUT 3 // AIN2 - P0.04

#define NRF_SAADC_BASE 0x40007000UL
// for Channel 0 only
#define PSELP REG32(NRF_SAADC_BASE + 0x510) // for P0.04
#define CONFIG REG32(NRF_SAADC_BASE + 0x518)
#define ENABLE REG32(NRF_SAADC_BASE + 0x500)
#define RESOLUTION REG32(NRF_SAADC_BASE + 0x5F0)
#define TASKS_START REG32(NRF_SAADC_BASE + 0x000)
#define TASKS_SAMPLE REG32(NRF_SAADC_BASE + 0x004)
#define TASKS_STOP REG32(NRF_SAADC_BASE + 0x008)

#define EVENTS_STARTED REG32(NRF_SAADC_BASE + 0x100)
#define EVENTS_END REG32(NRF_SAADC_BASE + 0x104)
#define EVENTS_DONE REG32(NRF_SAADC_BASE + 0x108)

#define RESULT_PTR REG32(NRF_SAADC_BASE + 0x62C)
#define RESULT_MAXCNT REG32(NRF_SAADC_BASE + 0x630)

static int16_t sample = 0; // SAADC stores sample as 16 bit two's complement value

void* mem_cpy(void* dest, const void* src, size_t n) {
	uint8_t* d = (uint8_t*)dest;
	const uint8_t* s = (const uint8_t*)src;

	while (n--) {
		*d++ = *s++;
	}

	return dest;
}

// Converts int16_t to ASCII decimal, returns length.
static uint8_t format_i16(int16_t value, uint8_t* out) {

	uint8_t tmp[5];
	uint8_t n = 0;
	uint8_t pos = 0;

	if (out == NULL)
		return 0;

	if (value == 0) {
		out[0] = (uint8_t)'0';
		return 1;
	}

	uint16_t magnitude;

	if (value < 0) {
		out[pos++] = (uint8_t)'-';

		magnitude = (uint16_t)(-(int32_t)value);
	} else {
		magnitude = (uint16_t)value;
	}

	while (magnitude != 0 && n < sizeof(tmp)) {
		uint16_t digit = magnitude % 10u;
		tmp[n++] = (uint8_t)('0' + digit);
		magnitude /= 10u;
	}

	for (uint8_t i = 0; i < n; i++) {
		out[pos + i] = tmp[n - 1 - i];
	}

	return pos + n;
}

static void init_saadc0(void) {
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

static void saadc_read(void) {
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

	uint8_t line[32];
	size_t line_len = 0;

	const char label[] = "SAMPLE: ";
	mem_cpy(&line[line_len], label, sizeof(label) - 1);
	line_len += sizeof(label) - 1;

	line_len += format_i16(sample, &line[line_len]);

	line[line_len++] = '\r';
	line[line_len++] = '\n';

	uarte_write((const char*)line, line_len);
}

int main(void) {
	init_uarte0();
	init_saadc0();

	P0_DIR |= (1u << PIN);

	while (1) {
		/* Discharge capacitor */
		P0_OUT &= ~(1u << PIN);
		uarte_write("DISCHARGE\r\n", sizeof("DISCHARGE\r\n") - 1);

		delay(6 * 1000 * 1000);

		saadc_read();

		/* Charge capacitor */
		P0_OUT |= (1u << PIN);
		uarte_write("CHARGE\r\n", sizeof("CHARGE\r\n") - 1);

		delay(6 * 1000 * 1000);

		saadc_read();
	}
}
