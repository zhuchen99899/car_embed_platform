################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/clock.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/components.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/cpu.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/device.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/idle.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/ipc.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/irq.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/kservice.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/mem.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/memheap.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/mempool.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/object.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/scheduler.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/signal.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/slab.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/thread.c \
D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/timer.c 

OBJS += \
./elab/3rd/rtt/rtthread_libraries/src/clock.o \
./elab/3rd/rtt/rtthread_libraries/src/components.o \
./elab/3rd/rtt/rtthread_libraries/src/cpu.o \
./elab/3rd/rtt/rtthread_libraries/src/device.o \
./elab/3rd/rtt/rtthread_libraries/src/idle.o \
./elab/3rd/rtt/rtthread_libraries/src/ipc.o \
./elab/3rd/rtt/rtthread_libraries/src/irq.o \
./elab/3rd/rtt/rtthread_libraries/src/kservice.o \
./elab/3rd/rtt/rtthread_libraries/src/mem.o \
./elab/3rd/rtt/rtthread_libraries/src/memheap.o \
./elab/3rd/rtt/rtthread_libraries/src/mempool.o \
./elab/3rd/rtt/rtthread_libraries/src/object.o \
./elab/3rd/rtt/rtthread_libraries/src/scheduler.o \
./elab/3rd/rtt/rtthread_libraries/src/signal.o \
./elab/3rd/rtt/rtthread_libraries/src/slab.o \
./elab/3rd/rtt/rtthread_libraries/src/thread.o \
./elab/3rd/rtt/rtthread_libraries/src/timer.o 

COMPILED_SRCS += \
./elab/3rd/rtt/rtthread_libraries/src/clock.src \
./elab/3rd/rtt/rtthread_libraries/src/components.src \
./elab/3rd/rtt/rtthread_libraries/src/cpu.src \
./elab/3rd/rtt/rtthread_libraries/src/device.src \
./elab/3rd/rtt/rtthread_libraries/src/idle.src \
./elab/3rd/rtt/rtthread_libraries/src/ipc.src \
./elab/3rd/rtt/rtthread_libraries/src/irq.src \
./elab/3rd/rtt/rtthread_libraries/src/kservice.src \
./elab/3rd/rtt/rtthread_libraries/src/mem.src \
./elab/3rd/rtt/rtthread_libraries/src/memheap.src \
./elab/3rd/rtt/rtthread_libraries/src/mempool.src \
./elab/3rd/rtt/rtthread_libraries/src/object.src \
./elab/3rd/rtt/rtthread_libraries/src/scheduler.src \
./elab/3rd/rtt/rtthread_libraries/src/signal.src \
./elab/3rd/rtt/rtthread_libraries/src/slab.src \
./elab/3rd/rtt/rtthread_libraries/src/thread.src \
./elab/3rd/rtt/rtthread_libraries/src/timer.src 

C_DEPS += \
./elab/3rd/rtt/rtthread_libraries/src/clock.d \
./elab/3rd/rtt/rtthread_libraries/src/components.d \
./elab/3rd/rtt/rtthread_libraries/src/cpu.d \
./elab/3rd/rtt/rtthread_libraries/src/device.d \
./elab/3rd/rtt/rtthread_libraries/src/idle.d \
./elab/3rd/rtt/rtthread_libraries/src/ipc.d \
./elab/3rd/rtt/rtthread_libraries/src/irq.d \
./elab/3rd/rtt/rtthread_libraries/src/kservice.d \
./elab/3rd/rtt/rtthread_libraries/src/mem.d \
./elab/3rd/rtt/rtthread_libraries/src/memheap.d \
./elab/3rd/rtt/rtthread_libraries/src/mempool.d \
./elab/3rd/rtt/rtthread_libraries/src/object.d \
./elab/3rd/rtt/rtthread_libraries/src/scheduler.d \
./elab/3rd/rtt/rtthread_libraries/src/signal.d \
./elab/3rd/rtt/rtthread_libraries/src/slab.d \
./elab/3rd/rtt/rtthread_libraries/src/thread.d \
./elab/3rd/rtt/rtthread_libraries/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
elab/3rd/rtt/rtthread_libraries/src/clock.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/%.o: ./elab/3rd/rtt/rtthread_libraries/src/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/components.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/components.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/cpu.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/device.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/device.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/idle.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/idle.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/ipc.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/ipc.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/irq.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/irq.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/kservice.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/kservice.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/mem.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/mem.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/memheap.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/memheap.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/mempool.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/mempool.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/object.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/object.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/scheduler.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/scheduler.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/signal.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/signal.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/slab.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/slab.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/thread.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/thread.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

elab/3rd/rtt/rtthread_libraries/src/timer.src: D:/work/Bilibili/cross_platform/elab/3rd/rtthread/rtthread_libraries/src/timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '


