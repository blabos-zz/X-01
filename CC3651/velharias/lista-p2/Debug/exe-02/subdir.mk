################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-02/exe-02.cpp \
../exe-02/matrix.cpp 

OBJS += \
./exe-02/exe-02.o \
./exe-02/matrix.o 

CPP_DEPS += \
./exe-02/exe-02.d \
./exe-02/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
exe-02/%.o: ../exe-02/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


