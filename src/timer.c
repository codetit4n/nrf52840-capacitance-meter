#include "timer.h"
#include "board.h"

static uint32_t et = 0;

void init_timer0(void) {
	TIMER_MODE_REG = 0;    // timer mode
	TIMER_BITMODE_REG = 3; // 32-bit
	TIMER_PRESCALER_REG = 4;
}

void start_timer(void) {
	// reset timer to 0
	TIMER_TASKS_CLEAR_REG = 1;

	// start timer
	TIMER_TASKS_START_REG = 1;
}

void stop_timer(void) {
	// capture timer
	TIMER_TASKS_CAPTURE0_REG = 1;

	// stop timer
	TIMER_TASKS_STOP_REG = 1;
}

uint32_t read_ctr(void) {
	et = TIMER_CC0_REG;
	return et;
}
