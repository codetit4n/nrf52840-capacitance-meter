#include "gpio.h"
#include "board.h"

inline void set_pin_output(uint8_t pin) {
	GPIO_P0_DIR_REG |= (1u << pin);
}

inline void set_pin_high(uint8_t pin) {
	GPIO_P0_OUT_REG |= (1u << pin);
}

inline void set_pin_low(uint8_t pin) {
	GPIO_P0_OUT_REG &= ~(1u << pin);
}
