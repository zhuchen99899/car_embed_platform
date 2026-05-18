################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.c \
../driver/Libraries/seekfree_libraries/common/common.c \
../driver/Libraries/seekfree_libraries/common/zf_assert.c 

OBJS += \
./driver/Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.o \
./driver/Libraries/seekfree_libraries/common/common.o \
./driver/Libraries/seekfree_libraries/common/zf_assert.o 

COMPILED_SRCS += \
./driver/Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.src \
./driver/Libraries/seekfree_libraries/common/common.src \
./driver/Libraries/seekfree_libraries/common/zf_assert.src 

C_DEPS += \
./driver/Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.d \
./driver/Libraries/seekfree_libraries/common/common.d \
./driver/Libraries/seekfree_libraries/common/zf_assert.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Libraries/seekfree_libraries/common/%.src: ../driver/Libraries/seekfree_libraries/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

driver/Libraries/seekfree_libraries/common/%.o: ./driver/Libraries/seekfree_libraries/common/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


