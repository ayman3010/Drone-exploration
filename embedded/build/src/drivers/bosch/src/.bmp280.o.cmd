cmd_src/drivers/bosch/src/bmp280.o := arm-none-eabi-gcc -Wp,-MD,src/drivers/bosch/src/.bmp280.o.d    -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src -Isrc/drivers/bosch/src -D__firmware__ -fno-exceptions -Wall -Wmissing-braces -fno-strict-aliasing -ffunction-sections -fdata-sections -Wdouble-promotion -std=gnu11 -DCRAZYFLIE_FW   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/CMSIS/CMSIS/DSP/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/libdw1000/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/FreeRTOS/include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/vendor/FreeRTOS/portable/GCC/ARM_CM4F   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/config   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/platform/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/deck/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/deck/drivers/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/esp32/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/hal/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/kalman_core   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/lighthouse   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/cpx   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/modules/interface/p2pDTR   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/kve   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/lighthouse   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/utils/interface/tdoa   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/FatFS   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/CMSIS/STM32F4xx/Include   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32_USB_Device_Library/Core/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32_USB_OTG_Driver/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/vl53l1   -I/Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/lib/vl53l1/core/inc   -I/Users/aymanatmani/Documents/INF3995-106/embedded/build/include/generated -fno-delete-null-pointer-checks --param=allow-store-data-races=0 -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -fno-var-tracking-assignments -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=date-time -DCC_HAVE_ASM_GOTO -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g3 -fno-math-errno -DARM_MATH_CM4 -D__FPU_PRESENT=1 -mfp16-format=ieee -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow -DSTM32F4XX -DSTM32F40_41xxx -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -Os -Werror   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/common/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/signal_manager/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/sensor_module/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/state_machine/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/receiver/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/transmitter/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/tasks/   -I/Users/aymanatmani/Documents/INF3995-106/embedded/src/   -c -o src/drivers/bosch/src/bmp280.o /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src/bmp280.c

source_src/drivers/bosch/src/bmp280.o := /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src/bmp280.c

deps_src/drivers/bosch/src/bmp280.o := \
    $(wildcard include/config/reg/spi3/enable//reg.h) \
    $(wildcard include/config/reg/spi3/enable.h) \
    $(wildcard include/config/reg/filter//reg.h) \
    $(wildcard include/config/reg/filter.h) \
    $(wildcard include/config/reg/standby/durn//reg.h) \
    $(wildcard include/config/reg/standby/durn.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src/../interface/bmp280.h \
    $(wildcard include/config/reg.h) \
    $(wildcard include/config/reg/standby/durn//pos.h) \
    $(wildcard include/config/reg/standby/durn//msk.h) \
    $(wildcard include/config/reg/standby/durn//len.h) \
    $(wildcard include/config/reg/filter//pos.h) \
    $(wildcard include/config/reg/filter//msk.h) \
    $(wildcard include/config/reg/filter//len.h) \
    $(wildcard include/config/reg/spi3/enable//pos.h) \
    $(wildcard include/config/reg/spi3/enable//msk.h) \
    $(wildcard include/config/reg/spi3/enable//len.h) \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src/../interface/bstdr_comm_support.h \
  /Users/aymanatmani/Documents/INF3995-106/embedded/crazyflie-firmware/src/drivers/bosch/src/../interface/bstdr_types.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stdint.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/stdint.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/machine/_default_types.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/features.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/_newlib_version.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_intsup.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/arm-none-eabi/include/sys/_stdint.h \
  /opt/homebrew/Cellar/gcc-arm-none-eabi/20200630/lib/gcc/arm-none-eabi/9.3.1/include/stdbool.h \

src/drivers/bosch/src/bmp280.o: $(deps_src/drivers/bosch/src/bmp280.o)

$(deps_src/drivers/bosch/src/bmp280.o):
