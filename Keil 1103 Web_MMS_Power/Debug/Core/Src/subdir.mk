################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/fonts.c \
../Core/Src/main.c \
../Core/Src/ssd1306.c \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f0xx.c 

OBJS += \
./Core/Src/fonts.o \
./Core/Src/main.o \
./Core/Src/ssd1306.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f0xx.o 

C_DEPS += \
./Core/Src/fonts.d \
./Core/Src/main.d \
./Core/Src/ssd1306.d \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/fonts.o: ../Core/Src/fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/fonts.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/ssd1306.o: ../Core/Src/ssd1306.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ssd1306.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32f0xx_hal_msp.o: ../Core/Src/stm32f0xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f0xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32f0xx_it.o: ../Core/Src/stm32f0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/system_stm32f0xx.o: ../Core/Src/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

