################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f042c6tx.s 

OBJS += \
./Core/Startup/startup_stm32f042c6tx.o 

S_DEPS += \
./Core/Startup/startup_stm32f042c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f042c6tx.o: ../Core/Startup/startup_stm32f042c6tx.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f042c6tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

