################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-09/exe-09.cpp 

OBJS += \
./exe-09/exe-09.o 

CPP_DEPS += \
./exe-09/exe-09.d 


# Each subdirectory must supply rules for building sources it contributes
exe-09/%.o: ../exe-09/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


