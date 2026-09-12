# nrf52840-capacitance-meter

> [!WARNING]
> Work in progress!

A simple [nRF52840](https://www.nordicsemi.com/Products/nRF52840)-based learning project for measuring small capacitors
using RC timing and ADC measurements.

## Current state

The RC charge/discharge circuit is working, and the nRF52840 is now reading the capacitor voltage through SAADC,
converting the readings to millivolts, and detecting discharge and charge thresholds.

<p align="center">
  <img src="assets/saadc-minicom.gif" alt="Capacitor charge and discharge demo" width="450">
</p>

<p align="center">
  <em>Minicom output showing the capacitor charge/discharge cycle and SAADC voltage readings.</em>
</p>

## Notes

- Some low-level code is reused from my earlier [nRF52840 bare-metal project](https://github.com/codetit4n/nrf52840-baremetal).
- The UARTE logging code is based on [this code](https://github.com/codetit4n/nrf52840-baremetal/blob/main/uarte-tx-only/src/main.c)
  from that project. Read more about it [here](https://loke.sh/blog/nrf52840-web-server/1-nrf52840-baremetal/#uarte-transmit-only-minimal-logger).

## Progress

See [PROGRESS.md](PROGRESS.md) for the implementation checklist.
