################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Individual/Individual.cpp 

OBJS += \
./Individual/Individual.o 

CPP_DEPS += \
./Individual/Individual.d 


# Each subdirectory must supply rules for building sources it contributes
Individual/%.o: ../Individual/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


