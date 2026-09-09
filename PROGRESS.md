# Progress

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
- [ ] Convert raw ADC readings to voltage
- [ ] Sample the capacitor while it is charging
- [ ] Add a hardware timer
- [ ] Measure time to the chosen voltage threshold
- [ ] Calculate capacitance from the measured charge time
- [ ] Compare calculated capacitance with the multimeter reading
- [ ] Test multiple capacitor values
- [ ] Record measurement error and repeatability

## Current target

Convert the SAADC raw reading into voltage and verify it against the multimeter.

After that, begin measuring the capacitor during the charging curve and add accurate timing.
