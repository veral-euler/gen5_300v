################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Eeprom.c \
../Core/Src/FOC_Basic.c \
../Core/Src/FOC_Basic_FF.c \
../Core/Src/FOC_H12.c \
../Core/Src/FOC_H12_data.c \
../Core/Src/FOC_LivGguard.c \
../Core/Src/FOC_LivGguard_data.c \
../Core/Src/FOC_MTPA_FF.c \
../Core/Src/MCU_Protections.c \
../Core/Src/MCU_Protections_data.c \
../Core/Src/NTC_Temp_Reading.c \
../Core/Src/Rate_Limiter.c \
../Core/Src/Sensor_Disconnection_Checks.c \
../Core/Src/Speed_Sensing.c \
../Core/Src/alignment_routine.c \
../Core/Src/fdcan.c \
../Core/Src/main.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c 

OBJS += \
./Core/Src/Eeprom.o \
./Core/Src/FOC_Basic.o \
./Core/Src/FOC_Basic_FF.o \
./Core/Src/FOC_H12.o \
./Core/Src/FOC_H12_data.o \
./Core/Src/FOC_LivGguard.o \
./Core/Src/FOC_LivGguard_data.o \
./Core/Src/FOC_MTPA_FF.o \
./Core/Src/MCU_Protections.o \
./Core/Src/MCU_Protections_data.o \
./Core/Src/NTC_Temp_Reading.o \
./Core/Src/Rate_Limiter.o \
./Core/Src/Sensor_Disconnection_Checks.o \
./Core/Src/Speed_Sensing.o \
./Core/Src/alignment_routine.o \
./Core/Src/fdcan.o \
./Core/Src/main.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o 

C_DEPS += \
./Core/Src/Eeprom.d \
./Core/Src/FOC_Basic.d \
./Core/Src/FOC_Basic_FF.d \
./Core/Src/FOC_H12.d \
./Core/Src/FOC_H12_data.d \
./Core/Src/FOC_LivGguard.d \
./Core/Src/FOC_LivGguard_data.d \
./Core/Src/FOC_MTPA_FF.d \
./Core/Src/MCU_Protections.d \
./Core/Src/MCU_Protections_data.d \
./Core/Src/NTC_Temp_Reading.d \
./Core/Src/Rate_Limiter.d \
./Core/Src/Sensor_Disconnection_Checks.d \
./Core/Src/Speed_Sensing.d \
./Core/Src/alignment_routine.d \
./Core/Src/fdcan.d \
./Core/Src/main.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -Wall -Wfatal-errors -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Eeprom.d ./Core/Src/Eeprom.o ./Core/Src/Eeprom.su ./Core/Src/FOC_Basic.d ./Core/Src/FOC_Basic.o ./Core/Src/FOC_Basic.su ./Core/Src/FOC_Basic_FF.d ./Core/Src/FOC_Basic_FF.o ./Core/Src/FOC_Basic_FF.su ./Core/Src/FOC_H12.d ./Core/Src/FOC_H12.o ./Core/Src/FOC_H12.su ./Core/Src/FOC_H12_data.d ./Core/Src/FOC_H12_data.o ./Core/Src/FOC_H12_data.su ./Core/Src/FOC_LivGguard.d ./Core/Src/FOC_LivGguard.o ./Core/Src/FOC_LivGguard.su ./Core/Src/FOC_LivGguard_data.d ./Core/Src/FOC_LivGguard_data.o ./Core/Src/FOC_LivGguard_data.su ./Core/Src/FOC_MTPA_FF.d ./Core/Src/FOC_MTPA_FF.o ./Core/Src/FOC_MTPA_FF.su ./Core/Src/MCU_Protections.d ./Core/Src/MCU_Protections.o ./Core/Src/MCU_Protections.su ./Core/Src/MCU_Protections_data.d ./Core/Src/MCU_Protections_data.o ./Core/Src/MCU_Protections_data.su ./Core/Src/NTC_Temp_Reading.d ./Core/Src/NTC_Temp_Reading.o ./Core/Src/NTC_Temp_Reading.su ./Core/Src/Rate_Limiter.d ./Core/Src/Rate_Limiter.o ./Core/Src/Rate_Limiter.su ./Core/Src/Sensor_Disconnection_Checks.d ./Core/Src/Sensor_Disconnection_Checks.o ./Core/Src/Sensor_Disconnection_Checks.su ./Core/Src/Speed_Sensing.d ./Core/Src/Speed_Sensing.o ./Core/Src/Speed_Sensing.su ./Core/Src/alignment_routine.d ./Core/Src/alignment_routine.o ./Core/Src/alignment_routine.su ./Core/Src/fdcan.d ./Core/Src/fdcan.o ./Core/Src/fdcan.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su

.PHONY: clean-Core-2f-Src

