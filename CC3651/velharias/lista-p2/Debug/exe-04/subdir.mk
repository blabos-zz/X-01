################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../exe-04/exe-04.cpp \
../exe-04/list.cpp \
../exe-04/matrix.cpp \
../exe-04/register.cpp 

OBJS += \
./exe-04/exe-04.o \
./exe-04/list.o \
./exe-04/matrix.o \
./exe-04/register.o 

CPP_DEPS += \
./exe-04/exe-04.d \
./exe-04/list.d \
./exe-04/matrix.d \
./exe-04/register.d 


# Each subdirectory must supply rules for building sources it contributes
exe-04/%.o: ../exe-04/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


