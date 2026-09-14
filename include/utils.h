#pragma once

#include <stddef.h>
#include <stdint.h>

void* mem_cpy(void* dest, const void* src, size_t n);
void* mem_set(void* s, int c, size_t n);
int mem_cmp(const void* s1, const void* s2, size_t n);
uint8_t format_u32(uint32_t value, uint8_t* out);
void log_volts(uint32_t milivolts);
void log_elapsed_time(uint32_t et);
void log_capacitance_nF(uint32_t et);
void log_capacitance_uF(uint32_t uF_int, uint8_t uF_hundreds, uint8_t uF_tens, uint8_t uF_ones);
void log_br(void);
void log_nl(void);
