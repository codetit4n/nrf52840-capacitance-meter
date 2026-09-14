#include <stdint.h>

#define NRF_P0_BASE 0x50000000UL
#define GPIO_P0_OUT_REG REG32(NRF_P0_BASE + 0x504)
#define GPIO_P0_DIR_REG REG32(NRF_P0_BASE + 0x514)

void set_pin_output(uint8_t pin);
void set_pin_high(uint8_t pin);
void set_pin_low(uint8_t pin);
