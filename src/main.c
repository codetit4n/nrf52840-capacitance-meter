#include "uarte.h"

static void delay(volatile uint32_t ctr) {
	while (ctr--) {
		__asm__ volatile("nop");
	}
}

int main(void) {
	init_uarte0();

	while (1) {
		uarte_write("Capacitance meter ready!\r\n",
			sizeof("Capacitance meter ready!\r\n") - 1);
		delay(10 * 1000 * 1000);
	}
}
