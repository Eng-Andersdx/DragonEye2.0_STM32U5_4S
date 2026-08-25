################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/TouchGFX/target/DragonEye/dragoneye_leds.c \
../Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.c 

C_DEPS += \
./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.d \
./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.d 

OBJS += \
./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.o \
./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/TouchGFX/target/DragonEye/%.o Application/User/TouchGFX/target/DragonEye/%.su Application/User/TouchGFX/target/DragonEye/%.cyclo: ../Application/User/TouchGFX/target/DragonEye/%.c Application/User/TouchGFX/target/DragonEye/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Utilities/JPEG -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I"C:/Users/HananHunain/Downloads/Bitbucket/DE_4/Repo/DragonEyeU5_4S/STM32CubeIDE/Application/User/TouchGFX/target/DragonEye" -I"C:/Users/HananHunain/Downloads/Bitbucket/DE_4/Repo/DragonEyeU5_4S/STM32CubeIDE/Application/User/TouchGFX/target/DragonEye/Components" -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-TouchGFX-2f-target-2f-DragonEye

clean-Application-2f-User-2f-TouchGFX-2f-target-2f-DragonEye:
	-$(RM) ./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.cyclo ./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.d ./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.o ./Application/User/TouchGFX/target/DragonEye/dragoneye_leds.su ./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.cyclo ./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.d ./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.o ./Application/User/TouchGFX/target/DragonEye/dragoneye_wifi.su

.PHONY: clean-Application-2f-User-2f-TouchGFX-2f-target-2f-DragonEye

