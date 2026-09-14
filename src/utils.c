#include "utils.h"
#include "uarte.h"

void* mem_cpy(void* dest, const void* src, size_t n) {
	uint8_t* d = (uint8_t*)dest;
	const uint8_t* s = (const uint8_t*)src;

	while (n--) {
		*d++ = *s++;
	}

	return dest;
}

uint8_t format_u32(uint32_t value, uint8_t* out) {

	uint8_t tmp[10];
	uint8_t n = 0;
	uint8_t pos = 0;

	if (out == NULL)
		return 0;

	if (value == 0) {
		out[0] = (uint8_t)'0';
		return 1;
	}

	while (value != 0 && n < sizeof(tmp)) {
		uint32_t digit = value % 10u;
		tmp[n++] = (uint8_t)('0' + digit);
		value /= 10u;
	}

	for (uint8_t i = 0; i < n; i++) {
		out[pos + i] = tmp[n - 1 - i];
	}

	return pos + n;
}

void log_volts(uint32_t milivolts) {

	uint8_t line[32];
	size_t line_len = 0;

	const char label[] = "VOLTAGE: ";
	mem_cpy(&line[line_len], label, sizeof(label) - 1);
	line_len += sizeof(label) - 1;

	line_len += format_u32(milivolts, &line[line_len]);

	line[line_len++] = ' ';
	line[line_len++] = 'm';
	line[line_len++] = 'V';
	line[line_len++] = '\r';
	line[line_len++] = '\n';

	uarte_write((const char*)line, line_len);
}

void log_elapsed_time(uint32_t et) {

	uint8_t line[32];
	size_t line_len = 0;

	const char label[] = "ELAPSED TIME: ";
	mem_cpy(&line[line_len], label, sizeof(label) - 1);
	line_len += sizeof(label) - 1;

	line_len += format_u32(et, &line[line_len]);

	line[line_len++] = ' ';
	line[line_len++] = 'u';
	line[line_len++] = 's';
	line[line_len++] = '\r';
	line[line_len++] = '\n';

	uarte_write((const char*)line, line_len);
}

void log_capacitance_nF(uint32_t et) {

	uint8_t line[32];
	size_t line_len = 0;

	const char label[] = "CAPACITANCE: ";
	mem_cpy(&line[line_len], label, sizeof(label) - 1);
	line_len += sizeof(label) - 1;

	line_len += format_u32(et, &line[line_len]);

	line[line_len++] = ' ';
	line[line_len++] = 'n';
	line[line_len++] = 'F';
	line[line_len++] = '\r';
	line[line_len++] = '\n';

	uarte_write((const char*)line, line_len);
}

void log_capacitance_uF(uint32_t uF_int, uint8_t uF_hundreds, uint8_t uF_tens, uint8_t uF_ones) {

	uint8_t line[50];
	size_t line_len = 0;

	const char label[] = "CAPACITANCE: ";
	mem_cpy(&line[line_len], label, sizeof(label) - 1);
	line_len += sizeof(label) - 1;

	line_len += format_u32(uF_int, &line[line_len]);

	line[line_len++] = '.';
	line[line_len++] = (uint8_t)('0' + uF_hundreds);
	line[line_len++] = (uint8_t)('0' + uF_tens);
	line[line_len++] = (uint8_t)('0' + uF_ones);
	line[line_len++] = ' ';
	line[line_len++] = 'u';
	line[line_len++] = 'F';
	line[line_len++] = '\r';
	line[line_len++] = '\n';

	uarte_write((const char*)line, line_len);
}

void log_br(void) {
	uint8_t line[2];

	line[0] = '\r';
	line[1] = '\n';

	uarte_write((const char*)line, 2);
}
