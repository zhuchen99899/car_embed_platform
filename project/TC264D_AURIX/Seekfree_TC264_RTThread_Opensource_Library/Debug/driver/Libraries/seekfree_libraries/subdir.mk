################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Libraries/seekfree_libraries/zf_ccu6_pit.c \
../driver/Libraries/seekfree_libraries/zf_eeprom.c \
../driver/Libraries/seekfree_libraries/zf_eru.c \
../driver/Libraries/seekfree_libraries/zf_eru_dma.c \
../driver/Libraries/seekfree_libraries/zf_gpio.c \
../driver/Libraries/seekfree_libraries/zf_gpt12.c \
../driver/Libraries/seekfree_libraries/zf_gtm_pwm.c \
../driver/Libraries/seekfree_libraries/zf_spi.c \
../driver/Libraries/seekfree_libraries/zf_stm_systick.c \
../driver/Libraries/seekfree_libraries/zf_uart.c \
../driver/Libraries/seekfree_libraries/zf_vadc.c 

OBJS += \
./driver/Libraries/seekfree_libraries/zf_ccu6_pit.o \
./driver/Libraries/seekfree_libraries/zf_eeprom.o \
./driver/Libraries/seekfree_libraries/zf_eru.o \
./driver/Libraries/seekfree_libraries/zf_eru_dma.o \
./driver/Libraries/seekfree_libraries/zf_gpio.o \
./driver/Libraries/seekfree_libraries/zf_gpt12.o \
./driver/Libraries/seekfree_libraries/zf_gtm_pwm.o \
./driver/Libraries/seekfree_libraries/zf_spi.o \
./driver/Libraries/seekfree_libraries/zf_stm_systick.o \
./driver/Libraries/seekfree_libraries/zf_uart.o \
./driver/Libraries/seekfree_libraries/zf_vadc.o 

COMPILED_SRCS += \
./driver/Libraries/seekfree_libraries/zf_ccu6_pit.src \
./driver/Libraries/seekfree_libraries/zf_eeprom.src \
./driver/Libraries/seekfree_libraries/zf_eru.src \
./driver/Libraries/seekfree_libraries/zf_eru_dma.src \
./driver/Libraries/seekfree_libraries/zf_gpio.src \
./driver/Libraries/seekfree_libraries/zf_gpt12.src \
./driver/Libraries/seekfree_libraries/zf_gtm_pwm.src \
./driver/Libraries/seekfree_libraries/zf_spi.src \
./driver/Libraries/seekfree_libraries/zf_stm_systick.src \
./driver/Libraries/seekfree_libraries/zf_uart.src \
./driver/Libraries/seekfree_libraries/zf_vadc.src 

C_DEPS += \
./driver/Libraries/seekfree_libraries/zf_ccu6_pit.d \
./driver/Libraries/seekfree_libraries/zf_eeprom.d \
./driver/Libraries/seekfree_libraries/zf_eru.d \
./driver/Libraries/seekfree_libraries/zf_eru_dma.d \
./driver/Libraries/seekfree_libraries/zf_gpio.d \
./driver/Libraries/seekfree_libraries/zf_gpt12.d \
./driver/Libraries/seekfree_libraries/zf_gtm_pwm.d \
./driver/Libraries/seekfree_libraries/zf_spi.d \
./driver/Libraries/seekfree_libraries/zf_stm_systick.d \
./driver/Libraries/seekfree_libraries/zf_uart.d \
./driver/Libraries/seekfree_libraries/zf_vadc.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Libraries/seekfree_libraries/%.src: ../driver/Libraries/seekfree_libraries/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

driver/Libraries/seekfree_libraries/%.o: ./driver/Libraries/seekfree_libraries/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


