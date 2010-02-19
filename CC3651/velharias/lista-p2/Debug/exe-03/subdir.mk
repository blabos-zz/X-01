################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-03/exe-03.cpp 

OBJS += \
./exe-03/exe-03.o 

CPP_DEPS += \
./exe-03/exe-03.d 


# Each subdirectory must supply rules for building sources it contributes
exe-03/%.o: ../exe-03/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


