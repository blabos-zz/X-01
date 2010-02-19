################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-05-06/exe-05-06.cpp \
../exe-05-06/list.cpp 

OBJS += \
./exe-05-06/exe-05-06.o \
./exe-05-06/list.o 

CPP_DEPS += \
./exe-05-06/exe-05-06.d \
./exe-05-06/list.d 


# Each subdirectory must supply rules for building sources it contributes
exe-05-06/%.o: ../exe-05-06/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


