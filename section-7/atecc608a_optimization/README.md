### About

This application can be used to measure processing time and energy consumption of the ATECC608A with different driver optimizations. The application calculates repeated SHA-256 hash values.

### Options

- To test energy consumption build with TEST_ENERGY=1.
- To read and store the context between function calls, build with ATCA_SAVE_CTX=1.
- To manually wake and put the device to sleep for power saving, build with ATCA_MANUAL_ONOFF=1.
- To disable the I2C reconfigure optimization which reduces the bus speed from 400 to 100kbit/s, build with NO_I2C_RECONF=1.