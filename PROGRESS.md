# Progress

## Status

**Complete.**

The core capacitance meter implementation is finished, tested across multiple capacitor values, and documented.

## Checklist

- [x] Created bare-metal nRF52840 project
- [x] Added UARTE logging
- [x] Built and tested a basic RC circuit
- [x] Measured the test components with a multimeter
  - Resistor: ~10.03 kΩ
  - Capacitor: ~11.23 µF
- [x] Verified capacitor charge/discharge behavior manually
- [x] Added GPIO-controlled charge/discharge using P0.27
- [x] Fixed common-ground wiring
- [x] Connected the RC measurement point to P0.04 / AIN2
- [x] Configured SAADC channel 0 for AIN2
- [x] Configured SAADC for:
  - single-ended input
  - internal 0.6 V reference
  - 1/6 gain
  - 5 µs acquisition time
  - 12-bit resolution
- [x] Added single-sample SAADC reading using EasyDMA
- [x] Printed raw ADC samples over UARTE
- [x] Verified discharged readings are near 0
- [x] Verified charged readings are stable at ~3430 raw ADC counts
- [x] Converted raw ADC readings to millivolts
- [x] Verified charged voltage is ~3.0 V
- [x] Added voltage-based discharge detection
  - Discharge threshold: 30 mV
- [x] Added voltage-based charge threshold detection
  - Charge threshold: ~1900 mV
  - Based on ~63.2% of the measured final voltage
- [x] Repeatedly sampled the capacitor during charge/discharge
- [x] Verified reliable threshold crossing with SAADC
- [x] Configured a 32-bit hardware timer
- [x] Configured timer for 1 µs resolution
- [x] Started timer when capacitor charging begins
- [x] Captured elapsed time when the charge threshold is reached
- [x] Printed measured charge time over UARTE
- [x] Calculated capacitance from the measured charge time
- [x] Added integer-based nF and µF output
- [x] Fixed arithmetic overflow for larger capacitor values
- [x] Compared calculated capacitance with multimeter readings
- [x] Tested multiple capacitor values
  - ~0.1 µF disc capacitor
  - 10 µF electrolytic capacitor
  - 22 µF electrolytic capacitor
  - 100 µF electrolytic capacitor
  - 1000 µF electrolytic capacitor
- [x] Recorded measurement error and repeatability
- [x] Finished documentation
  - Circuit diagram
  - Hardware setup
  - Measurement demos
  - Measurement comparison
  - README

## Final result

A working bare-metal capacitance meter using RC timing, the nRF52840 SAADC, and a hardware timer.

Tested from approximately 0.1 µF to 1000 µF, with measurements compared against a multimeter.
