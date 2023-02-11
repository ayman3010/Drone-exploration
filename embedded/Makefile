# The firmware uses the Kbuild build system. There are 'Kbuild' files in this
# example that outlays what needs to be built. (check src/Kbuild).
#
# The firmware is configured using options in Kconfig files, the
# values of these end up in the .config file in the firmware directory.
#
# By setting the OOT_CONFIG (it is '$(PWD)/oot-config' by default) environment
# variable you can provide a custom configuration. It is important that you
# enable the app-layer. See app-config in this directory for example.

#
# We want to execute the main Makefile for the firmware project,
# it will handle the build for us.
#
CRAZYFLIE_BASE := $(PWD)/crazyflie-firmware

#
# To include header files from other directories
#
EXTRA_CFLAGS += -I$(PWD)/src/common/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/signal_manager/
EXTRA_CFLAGS += -I$(PWD)/src/sensor_module/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/state_machine/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/receiver/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/transmitter/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/p2p/
EXTRA_CFLAGS += -I$(PWD)/src/tasks/battery/
EXTRA_CFLAGS += -I$(PWD)/src/

#
# We override the default OOT_CONFIG here, we could also name our config
# to oot-config and that would be the default.
#

OOT_CONFIG := $(PWD)/app-config
OOT_USES_CXX := 1
include $(CRAZYFLIE_BASE)/tools/make/oot.mk

myclean:
	rm -rf build/
	rm -f *.o
	rm -f src/*.o
	rm -f src/tasks/state_machine/*.o
	rm -f src/tasks/receiver/*.o
	rm -f src/tasks/trasmitter/*.o
	rm -f src/sensor_module/*.o
	rm -f src/signal_manager/*.o
	rm -f src/tasks/*.o
	rm -f src/tasks/*.*.cmd