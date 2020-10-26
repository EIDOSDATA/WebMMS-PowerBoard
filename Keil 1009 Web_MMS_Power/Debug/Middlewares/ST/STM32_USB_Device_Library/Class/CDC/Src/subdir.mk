################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F042x6 -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/Code/stm32/Web_MMS_Power/Drivers/CMSIS/Include" -I"D:/Code/stm32/Web_MMS_Power/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/Code/stm32/Web_MMS_Power/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/App" -I"D:/Code/stm32/Web_MMS_Power/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/Code/stm32/Web_MMS_Power/USB_DEVICE/Target" -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

