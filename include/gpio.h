#include <stdint.h>

#define NRF_P0_BASE 0x50000000UL
#define P0_OUT REG32(NRF_P0_BASE + 0x504)
#define P0_DIR REG32(NRF_P0_BASE + 0x514)

void set_pin_output(uint8_t pin);
void set_pin_high(uint8_t pin);
void set_pin_low(uint8_t pin);
