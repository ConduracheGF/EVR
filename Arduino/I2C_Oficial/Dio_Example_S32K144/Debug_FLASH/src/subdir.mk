################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/7-segment-display.c \
../src/AS1115.c \
../src/SevenSegments.c \
../src/main.c 

OBJS += \
./src/7-segment-display.o \
./src/AS1115.o \
./src/SevenSegments.o \
./src/main.o 

C_DEPS += \
./src/7-segment-display.d \
./src/AS1115.d \
./src/SevenSegments.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/7-segment-display.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


