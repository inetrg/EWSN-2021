### About

This application can be used to measure processing time, energy consumption, stack size and memory usage of the ECDH operation using the uECC library.

### Options

#### Random Number Generator
There are two RNGs available: SHA256-PRNG (default) and RIOT HWRNG. They can be configured in *menuconfig* under `System -> Pseudo-Random Number Generator API [PRNG] -> PRNG Implementation`.

#### Energy Consumption
- Set TEST_ENERGY=1 when building the application.
- For further information, please refer to [section-5](../../section-5/README.md).

#### Stack Size
- Set TEST_STACK=1 when building the application.
- Minimal application prints size of used stack at the end of the program.

#### Firmware Size
- Set TEST_MEM=1 when compiling the application.
- The binary can be analyzed with common tools such as `readelf`.