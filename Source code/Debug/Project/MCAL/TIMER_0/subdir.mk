################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/MCAL/TIMER_0/Timer0_program.c 

OBJS += \
./Project/MCAL/TIMER_0/Timer0_program.o 

C_DEPS += \
./Project/MCAL/TIMER_0/Timer0_program.d 


# Each subdirectory must supply rules for building sources it contributes
Project/MCAL/TIMER_0/%.o: ../Project/MCAL/TIMER_0/%.c Project/MCAL/TIMER_0/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


