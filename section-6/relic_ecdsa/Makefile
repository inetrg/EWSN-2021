# name of the application
APPLICATION = crypto-ewsn2020_ecdsa

USEPKG += relic

ifeq (1, $(TEST_ENERGY))
	CFLAGS += -DTEST_ENERGY=1
endif

ifeq (1, $(RIOT_HWRNG))
	CFLAGS+=-DRIOT_HWRNG
endif

ifeq (1, $(TEST_MEM))
	CFLAGS += -DTEST_MEM=1
else
	ifeq (1, $(TEST_STACK))
		CFLAGS+=-DTEST_STACK=1
		USEMODULE += ps
		CFLAGS +=-DDEVELHELP=1
	else
		USEMODULE += xtimer
		FEATURES_REQUIRED += periph_gpio
	endif
endif

CFLAGS += -DTHREAD_STACKSIZE_MAIN=\(12*THREAD_STACKSIZE_DEFAULT\)

export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWORD=32 -DFP_PRIME=256 -DWITH="BN;MD;DV;FP;EP;CP" -DSEED=RIOTRND -DEP_METHD="PROJC;LWNAF;COMBS;INTER" -DEP_PRECO=on

#defualt -DEP_METHD="PROJC;LWNAF;COMBS;INTER -DEP_PRECO=on
# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

include $(RIOTBASE)/Makefile.include
