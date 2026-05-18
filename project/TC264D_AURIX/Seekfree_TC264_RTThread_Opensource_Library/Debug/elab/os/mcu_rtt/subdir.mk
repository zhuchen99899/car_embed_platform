################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/Bilibili/cross_platform/elab/os/mcu_rtt/cmsis_rtthread.c \
D:/work/Bilibili/cross_platform/elab/os/mcu_rtt/os_systick.c 

OBJS += \
./elab/os/mcu_rtt/cmsis_rtthread.o \
./elab/os/mcu_rtt/os_systick.o 

COMPILED_SRCS += \
./elab/os/mcu_rtt/cmsis_rtthread.src \
./elab/os/mcu_rtt/os_systick.src 

C_DEPS += \
./elab/os/mcu_rtt/cmsis_rtthread.d \
./elab/os/mcu_rtt/os_systick.d 


# Each subdirectory must supply rules for building sources it contributes
elab/os/mcu_rtt/cmsis_rtthread.src: D:/work/Bilibili/cross_platform/elab/os/mcu_rtt/cmsis_rtthread.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/os/mcu_rtt/%.o: ./elab/os/mcu_rtt/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

elab/os/mcu_rtt/os_systick.src: D:/work/Bilibili/cross_platform/elab/os/mcu_rtt/os_systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '


