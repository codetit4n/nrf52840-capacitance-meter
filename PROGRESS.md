# Progress

## Checklist

- [x] Created bare-metal nRF52840 project
- [x] Added UARTE logging
- [x] Built and tested a basic RC circuit
- [x] Measured test components with the UT61B+
  - Resistor: ~10.03 kΩ
  - Capacitor: ~11.23 µF
- [x] Verified capacitor charge/discharge behavior
- [x] Added GPIO-controlled charge/discharge using P0.27
- [x] Fixed common-ground wiring
- [x] Connected the RC measurement point to P0.04 / AIN2
- [ ] Configure SAADC
- [ ] Read the capacitor voltage on P0.04
- [ ] Print raw ADC readings over UARTE
- [ ] Convert ADC readings to voltage
- [ ] Add a hardware timer
- [ ] Measure time to a chosen voltage threshold
- [ ] Calculate capacitance
- [ ] Compare results with the UT61B+
- [ ] Test multiple capacitor values

## Current target

Read the RC midpoint voltage using SAADC on P0.04 / AIN2.
