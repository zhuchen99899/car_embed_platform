################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/IfxCcu6.c 

OBJS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/IfxCcu6.o 

COMPILED_SRCS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/IfxCcu6.src 

C_DEPS += \
./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/IfxCcu6.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/%.src: ../driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/%.o: ./driver/Libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/Std/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


