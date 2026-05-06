################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/platform.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/vl53l5cx_api.c \
../Core/Src/vl53l5cx_plugin_detection_thresholds.c \
../Core/Src/vl53l5cx_plugin_motion_indicator.c \
../Core/Src/vl53l5cx_plugin_xtalk.c 

OBJS += \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/platform.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/vl53l5cx_api.o \
./Core/Src/vl53l5cx_plugin_detection_thresholds.o \
./Core/Src/vl53l5cx_plugin_motion_indicator.o \
./Core/Src/vl53l5cx_plugin_xtalk.o 

C_DEPS += \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/platform.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/vl53l5cx_api.d \
./Core/Src/vl53l5cx_plugin_detection_thresholds.d \
./Core/Src/vl53l5cx_plugin_motion_indicator.d \
./Core/Src/vl53l5cx_plugin_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/platform.cyclo ./Core/Src/platform.d ./Core/Src/platform.o ./Core/Src/platform.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/vl53l5cx_api.cyclo ./Core/Src/vl53l5cx_api.d ./Core/Src/vl53l5cx_api.o ./Core/Src/vl53l5cx_api.su ./Core/Src/vl53l5cx_plugin_detection_thresholds.cyclo ./Core/Src/vl53l5cx_plugin_detection_thresholds.d ./Core/Src/vl53l5cx_plugin_detection_thresholds.o ./Core/Src/vl53l5cx_plugin_detection_thresholds.su ./Core/Src/vl53l5cx_plugin_motion_indicator.cyclo ./Core/Src/vl53l5cx_plugin_motion_indicator.d ./Core/Src/vl53l5cx_plugin_motion_indicator.o ./Core/Src/vl53l5cx_plugin_motion_indicator.su ./Core/Src/vl53l5cx_plugin_xtalk.cyclo ./Core/Src/vl53l5cx_plugin_xtalk.d ./Core/Src/vl53l5cx_plugin_xtalk.o ./Core/Src/vl53l5cx_plugin_xtalk.su

.PHONY: clean-Core-2f-Src

