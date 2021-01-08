### About
Compare SHA-256 with different software packages.

### Options
- To use the RIOT hashes software module (instead of hardware) you need to change the default configuration in *menuconfig*. From the top menu go to `System -> Hashes -> SHA-256` and choose `Software`.

- To switch between different software implementations you need to enable one during compilation:
   - TEST_RIOT=1
   - TEST_RELIC=1
   - TEST_WOLFSSL=1
   - TEST_TINYCRYPT=1
   - TEST_CIFRA=1

- To enable/disable measurement modes:
   - TEST_STACK=1 to output the used stack size.
   - USE_XTIMER=1 for measurements based on a system timer.
   - MODE_GPIO=1 for measurements using a gpio.