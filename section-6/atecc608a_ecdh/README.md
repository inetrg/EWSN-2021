### About

This application can be used to measure processing time, energy consumption, stack size and memory usage of the hardware accelerated ECDH operation using the ATECC608A device using the CryptoAuth Lib.

This application requires both *config zone* and *data zone* to be configured and locked as described in [atecc608a_configure_and_lock](../atecc608a_configure_and_lock/README.md).

### Options
This application runs on a Nordic nrf52840dk with an ATECC608A extension.

#### Energy Consumption
- Set TEST_ENERGY=1 when building the application.
- For further information, please refer to [section-5](../../section-5/README.md).

#### Stack Size
- Set TEST_STACK=1 when building the application.
- Minimal application prints size of used stack at the end of the program.

#### Firmware Size
- Set TEST_MEM=1 when compiling the application.
- The binary can be analyzed with common tools such as `readelf`.