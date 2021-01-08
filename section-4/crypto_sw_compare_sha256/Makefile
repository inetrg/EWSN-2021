# name of the application
APPLICATION = crypto_sw_compare_sha256

# If no BOARD is found in the environment, use this default:
BOARD ?= nrf52840dk

ifeq (1, $(TEST_STACK))
  CFLAGS += -DTEST_STACK
  USEMODULE += ps
endif

ifeq (1, $(USE_XTIMER))
  CFLAGS += -DUSE_XTIMER
  USEMODULE += xtimer
endif

ifeq (1, $(MODE_GPIO))
  CFLAGS += -DMODE_GPIO
  FEATURES_REQUIRED += periph_gpio
endif


# RIOT
ifeq (1, $(TEST_RIOT))
  export TEST_KCONFIG ?= 1
  CFLAGS += -DTEST_RIOT=1
  USEMODULE += hashes
endif

# RELIC
ifeq (1, $(TEST_RELIC))
	CFLAGS += -DTEST_RELIC=1
	USEPKG += relic
	# The rest of the parameters are configuration parameters for RELIC described in its documentation.
	export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWORD=32 -DFP_PRIME=255 -DWITH="MD" -DSEED=RIOTRND -DRAND=HASH -DMD_METHD=SHONE
endif

# tinycrypt
ifeq (1, $(TEST_TINYCRYPT))
	CFLAGS += -DTEST_TINYCRYPT=1
	USEPKG += tinycrypt
endif

# woldssl
ifeq (1, $(TEST_WOLFSSL))
	CFLAGS += -DTEST_WOLFSSL=1
	USEPKG += wolfssl
	USEMODULE += wolfcrypt
endif

# cifra
ifeq (1, $(TEST_CIFRA))
	CFLAGS += -DTEST_CIFRA=1
	USEPKG += cifra
endif

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
