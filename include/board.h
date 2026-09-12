#include <stdint.h>

#define REG32(addr) (*(volatile uint32_t*)(addr))

#define DISCHARGE_THRESHOLD_MV 30 // considered fully discharged below 30 mV
#define CHARGE_THRESHOLD_MV 1900  // ~63.2% of measured final voltage (~3015 mV)

#define PIN 27	    // P0.27
#define ADC_INPUT 3 // AIN2 - P0.04
