cmd_src/utils/src/tdoa/tdoaEngine.o := arm-none-eabi-gcc -Wp,-MD,src/utils/src/tdoa/.tdoaEngine.o.d    -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/src -Isrc/utils/src -D__firmware__ -fno-exceptions -Wall -Wmissing-braces -fno-strict-aliasing -ffunction-sections -fdata-sections -Wdouble-promotion -std=gnu11 -DCRAZYFLIE_FW   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/CMSIS/CMSIS/DSP/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/libdw1000/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/FreeRTOS/include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/FreeRTOS/portable/GCC/ARM_CM4F   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/config   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/platform/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/deck/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/deck/drivers/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/esp32/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/hal/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/kalman_core   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/lighthouse   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/cpx   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/p2pDTR   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/kve   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/lighthouse   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/FatFS   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/CMSIS/STM32F4xx/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32_USB_Device_Library/Core/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32_USB_OTG_Driver/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/vl53l1   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/vl53l1/core/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/build/include/generated -fno-delete-null-pointer-checks --param=allow-store-data-races=0 -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -fno-var-tracking-assignments -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=date-time -DCC_HAVE_ASM_GOTO -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g3 -fno-math-errno -DARM_MATH_CM4 -D__FPU_PRESENT=1 -mfp16-format=ieee -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow -DSTM32F4XX -DSTM32F40_41xxx -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -Os -Werror   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/common/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/signal_manager/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/sensor_module/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/state_machine/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/receiver/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/transmitter/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/   -c -o src/utils/src/tdoa/tdoaEngine.o /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/src/tdoa/tdoaEngine.c

source_src/utils/src/tdoa/tdoaEngine.o := /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/src/tdoa/tdoaEngine.c

deps_src/utils/src/tdoa/tdoaEngine.o := \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/string.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/_ansi.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/newlib.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/_newlib_version.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/config.h \
    $(wildcard include/config/h//.h) \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/machine/ieeefp.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/features.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/reent.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/_ansi.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stddef.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_types.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/machine/_types.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/machine/_default_types.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/lock.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/cdefs.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_locale.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/strings.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/string.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/debug.h \
    $(wildcard include/config/debug/print/on/uart1.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/config/config.h \
    $(wildcard include/config/h/.h) \
    $(wildcard include/config/block/address.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/interface/nrf24l01.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stdbool.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/interface/nRF24L01reg.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/config/trace.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/hal/interface/usec_time.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stdint.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/stdint.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_intsup.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_stdint.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/console.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/eprintf.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stdarg.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa/tdoaEngine.h \
    $(wildcard include/config/deck/loco/longer/range.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa/tdoaStorage.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/stabilizer_types.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/hal/interface/imu_types.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/lighthouse/lighthouse_types.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/clockCorrectionEngine.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa/tdoaStats.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/inttypes.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/statsCnt.h \
    $(wildcard include/config/debug/log/enable.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/log.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa/tdoaStats.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/physicalConstants.h \

src/utils/src/tdoa/tdoaEngine.o: $(deps_src/utils/src/tdoa/tdoaEngine.o)

$(deps_src/utils/src/tdoa/tdoaEngine.o):
