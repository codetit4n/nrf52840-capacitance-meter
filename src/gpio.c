#include "gpio.h"
#include "board.h"

inline void set_pin_output(uint8_t pin) {
	P0_DIR |= (1u << pin);
}

inline void set_pin_high(uint8_t pin) {
	P0_OUT |= (1u << pin);
}

inline void set_pin_low(uint8_t pin) {
	P0_OUT &= ~(1u << pin);
}
