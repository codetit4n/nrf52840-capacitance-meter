#include <stdint.h>

#define REG32(addr) (*(volatile uint32_t*)(addr))

static inline void delay(volatile uint32_t ctr) {
	while (ctr--) {
		__asm__ volatile("nop");
	}
}
