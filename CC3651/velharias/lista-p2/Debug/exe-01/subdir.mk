################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-01/exe-01.cpp \
../exe-01/matrix.cpp 

OBJS += \
./exe-01/exe-01.o \
./exe-01/matrix.o 

CPP_DEPS += \
./exe-01/exe-01.d \
./exe-01/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
exe-01/%.o: ../exe-01/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


