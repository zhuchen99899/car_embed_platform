################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/IfxAsclin_Spi.c 

OBJS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/IfxAsclin_Spi.o 

COMPILED_SRCS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/IfxAsclin_Spi.src 

C_DEPS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/IfxAsclin_Spi.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/%.src: ../driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/%.o: ./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Spi/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


