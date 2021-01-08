### How to build and execute applications in RIOT

1. Navigate to an application folder. The applications are organized according to the sections of the paper: [section-4](section-4/), [section-5](section-5/), [section-6](section-6/), [section-7](section-7/). Please note that some folders contain subfolders. To proceed, navigate to the specific experiment of interest.
2. To compile an application, you will need to use *make* and specify the target board:

    `BOARD=<target board> make`
1. To flash an application to a board:

    `BOARD=<target board> make flash`
1. To access the terminal:

    `BOARD=<target board> make term`
1. For specific experiments you need to set compiler flags or apply configurations with the *menuconfig* tool. The documentation in the respective application folder lists available modes.
    - Set compiler flags before the *make* command (e.g. `USE_XTIMER=1 BOARD=<target board> make`).
    - Enter *menuconfig* via `BOARD=<target board> menuconfig`. After configuring, hit *S* and enter. Then *Q* to quit.
2. For further information please refer to the [RIOT Getting Started Guide](https://doc.riot-os.org/getting-started.html).

### Target Boards

- Phytec IoT Kit 2 with **MKW22D**: `pba-d-01-kw2x` .
- Silicon Labs Pearl Gecko **EFM32**: `slstk3402a` .
- Nordic nRF52840dk **NRF52**: `nRF52840dk` .
- (Optionally with Microchip or Adafruit ATECC608A extension board).