### About

This application can be used to measure the processing time, energy consumption and memory usage of SHA-256 and HMAC-SHA256 implementations as well as AES ECB-128 and AES CBC-128 encryption and decryption.

### Algorithm Options
- SHA256=1
- HMAC=1 (32 Byte HMAC Key)
- HMAC_64=1 (64 Byte HMAC Key – not compatible with ATECC608A)
- AES_ECB=1
- AES_CBC=1
- INPUT_512=1 (set input size of 512 Byte, default is 32 Byte)

### Experiment Options
#### Processing Time
- All boards are configured to use cryptographic hardware acceleration, when available. If you want to run the RIOT crypto and hash software implementations, manually configure it in *menuconfig*.
    - For hashes: From the top menu go to `System -> Hashes -> SHA-256` and choose `Software`.
    - For ciphers: From the top menu go to `System -> Crypto -> AES` and choose `Software`.

- When using nrf52840 with the ATECC608A extension.
Open *menuconfig*. From the top menu, go to `Packages` and enable *Microchip CryptoAuth Library*. From the top menu, go to `System -> Crypto -> AES` or `System -> Hashes -> SHA-256` and also enable *Microchip CryptoAuth Library*.

#### Energy Consumption

- Enable cryptographic operation implementation in *menuconfig* as described above
- To enable energy measurements for one algorithm when compiling the application:
    - TEST_ENERGY_SHA256=1
    - TEST_ENERGY_HMAC_SHA256=1
    - TEST_ENERGY_AES_ECB_<ENC|DEC>=1
    - TEST_ENERGY_AES_CBC_<ENC|DEC>=1
- The energy measurement requires a trigger applied to an I/Os which synchronized execution with the sampling multimeter. We refer to the [code](energy_sha256.c#L80) for further details.
- Alternatively, disable the I/O synchronization when compiling the application by using the system timer:
  - USE_XTIMER=1

**Note**: If you're not using the I/O method to synchronize a measuring instrument, you must set USE_XTIMER=1, otherwise the program will wait for the gpio input and never start.

#### Stack Size
- Set TEST_STACK=1 when compiling the application.
- Enable cryptographic operation implementation in *menuconfig* as described above.
- Minimal application prints size of used stack at the end of the program.

##### Firmware Size
- Set TEST_MEM=1 when compiling the application.
- Enable cryptographic operation in *menuconfig* as described above.
- The binary can be analyzed with common tools such as `readelf`.
