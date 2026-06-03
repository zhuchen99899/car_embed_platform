################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/Bilibili/cross_platform/elab/edf/normal/elab_i2c.c \
D:/work/Bilibili/cross_platform/elab/edf/normal/elab_pin.c 

OBJS += \
./elab/edf/normal/elab_i2c.o \
./elab/edf/normal/elab_pin.o 

COMPILED_SRCS += \
./elab/edf/normal/elab_i2c.src \
./elab/edf/normal/elab_pin.src 

C_DEPS += \
./elab/edf/normal/elab_i2c.d \
./elab/edf/normal/elab_pin.d 


# Each subdirectory must supply rules for building sources it contributes
elab/edf/normal/elab_i2c.src: D:/work/Bilibili/cross_platform/elab/edf/normal/elab_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/edf/normal/%.o: ./elab/edf/normal/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

elab/edf/normal/elab_pin.src: D:/work/Bilibili/cross_platform/elab/edf/normal/elab_pin.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '


