################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/MCAL/GIE/GIE_program.c 

OBJS += \
./Project/MCAL/GIE/GIE_program.o 

C_DEPS += \
./Project/MCAL/GIE/GIE_program.d 


# Each subdirectory must supply rules for building sources it contributes
Project/MCAL/GIE/%.o: ../Project/MCAL/GIE/%.c Project/MCAL/GIE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


