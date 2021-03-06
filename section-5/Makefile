# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

APPLICATION = crypto-ewsn2020

FEATURES_REQUIRED += periph_gpio

# this has to be anabled in *menuconfig* now!
# ifneq (, $(NO_I2C_RECONF))
# 	CFLAGS+=-DNO_I2C_RECONF=1
# else
# 	FEATURES_OPTIONAL += periph_i2c_reconfigure
# endif

ifeq (1, $(INPUT_512))
	CFLAGS +=-DINPUT_512=1
endif

ifeq (1, $(SHA256))
	CFLAGS +=-DSHA256=1
endif

ifeq (1, $(HMAC))
	CFLAGS +=-DHMAC=1
endif

ifeq (1, $(HMAC_64))
	CFLAGS +=-DHMAC=1
	CFLAGS +=-DHMAC_64=1
endif

ifeq (1, $(AES_CBC))
	CFLAGS +=-DAES_CBC=1
	CFLAGS +=-DTEST_AES_KEY=1
endif

ifeq (1, $(AES_ECB))
	CFLAGS +=-DAES_ECB=1
	CFLAGS +=-DTEST_AES_KEY=1
endif

ifeq (1, $(TEST_AES_KEY))
	CFLAGS +=-DTEST_AES_KEY=1
endif

ifeq (1, $(TEST_STACK))
	CFLAGS +=-DTEST_STACK=1
	CFLAGS +=-DDEVELHELP=1
	USEMODULE += ps
endif

ifeq (1, $(TEST_MEM))
	CFLAGS +=-DTEST_MEM=1
endif

ifneq (, $(TEST_ENERGY%))
	CFLAGS+=-DTEST_ENERGY=1
	USEMODULE += xtimer
endif

# this is only used by gecko board to disable board init stuff that consumes much current
ifeq (1, $(USE_XTIMER))
	CFLAGS += -DUSE_XTIMER
endif

ifneq (, $(TEST_ENERGY))
	CFLAGS+=-DTEST_ENERGY=1
endif

ifneq (, $(TEST_ENERGY_ITER))
	CFLAGS +=-DTEST_ENERGY_ITER=$(TEST_ENERGY_ITER)
else
	CFLAGS +=-DTEST_ENERGY_ITER=1100
endif

ifeq (1, $(TEST_ENERGY_SHA256))
	CFLAGS +=-DTEST_ENERGY_SHA256=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (1, $(TEST_ENERGY_HMAC_SHA256))
	CFLAGS +=-DTEST_ENERGY_HMAC_SHA256=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (1, $(TEST_ENERGY_AES_CBC_ENC))
	CFLAGS +=-DTEST_ENERGY_AES_CBC_ENC=1
	CFLAGS +=-DTEST_ENERGY_AES_CBC=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (1, $(TEST_ENERGY_AES_CBC_DEC))
	CFLAGS +=-DTEST_ENERGY_AES_CBC_DEC=1
	CFLAGS +=-DTEST_ENERGY_AES_CBC=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (1, $(TEST_ENERGY_AES_ECB_ENC))
	CFLAGS +=-DTEST_ENERGY_AES_ECB_ENC=1
	CFLAGS +=-DTEST_ENERGY_AES_ECB=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (1, $(TEST_ENERGY_AES_ECB_DEC))
	CFLAGS +=-DTEST_ENERGY_AES_ECB_DEC=1
	CFLAGS +=-DTEST_ENERGY_AES_ECB=1
	CFLAGS+=-DTEST_ENERGY=1
endif

ifeq (pba-d-01-kw2x, $(BOARD))
	# Kinetis Hardware
	CFLAGS += -DFREESCALE_MMCAU -Wno-unused-function
	USEMODULE += lib_mmcau
endif

ifeq (nrf52840dk, $(BOARD))
	CFLAGS += -DARM_CRYPTOCELL
	USEMODULE += lib_cryptocell
endif

export TEST_KCONFIG ?= 1

include $(RIOTBASE)/Makefile.include
