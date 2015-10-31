################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Logic/Constants.cpp \
../Logic/GameLogic.cpp 

OBJS += \
./Logic/Constants.o \
./Logic/GameLogic.o 

CPP_DEPS += \
./Logic/Constants.d \
./Logic/GameLogic.d 


# Each subdirectory must supply rules for building sources it contributes
Logic/%.o: ../Logic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


