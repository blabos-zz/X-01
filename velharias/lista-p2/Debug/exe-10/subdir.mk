################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-10/exe-10.cpp 

OBJS += \
./exe-10/exe-10.o 

CPP_DEPS += \
./exe-10/exe-10.d 


# Each subdirectory must supply rules for building sources it contributes
exe-10/%.o: ../exe-10/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


