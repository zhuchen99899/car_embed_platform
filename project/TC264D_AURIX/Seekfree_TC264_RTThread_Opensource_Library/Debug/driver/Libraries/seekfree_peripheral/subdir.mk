################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Libraries/seekfree_peripheral/SEEKFREE_18TFT.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_7725.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_7725_UART.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_FONT.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_FUN.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_ICM20602.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_IIC.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_IPS114_SPI.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_IPS200_PARALLEL8.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_L3G4200D.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_MMA8451.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_MPU6050.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_MT9V03X.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_OLED.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_RDA5807.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_VIRSCO.c \
../driver/Libraries/seekfree_peripheral/SEEKFREE_WIRELESS.c 

OBJS += \
./driver/Libraries/seekfree_peripheral/SEEKFREE_18TFT.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725_UART.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FONT.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FUN.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_ICM20602.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IIC.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS114_SPI.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS200_PARALLEL8.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_L3G4200D.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MMA8451.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MPU6050.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MT9V03X.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_OLED.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_RDA5807.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_VIRSCO.o \
./driver/Libraries/seekfree_peripheral/SEEKFREE_WIRELESS.o 

COMPILED_SRCS += \
./driver/Libraries/seekfree_peripheral/SEEKFREE_18TFT.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725_UART.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FONT.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FUN.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_ICM20602.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IIC.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS114_SPI.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS200_PARALLEL8.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_L3G4200D.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MMA8451.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MPU6050.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MT9V03X.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_OLED.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_RDA5807.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_VIRSCO.src \
./driver/Libraries/seekfree_peripheral/SEEKFREE_WIRELESS.src 

C_DEPS += \
./driver/Libraries/seekfree_peripheral/SEEKFREE_18TFT.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_7725_UART.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FONT.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_FUN.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_ICM20602.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IIC.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS114_SPI.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_IPS200_PARALLEL8.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_L3G4200D.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MMA8451.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MPU6050.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_MT9V03X.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_OLED.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_RDA5807.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_VIRSCO.d \
./driver/Libraries/seekfree_peripheral/SEEKFREE_WIRELESS.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Libraries/seekfree_peripheral/%.src: ../driver/Libraries/seekfree_peripheral/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/work/Bilibili/cross_platform/project/TC264D_AURIX/Seekfree_TC264_RTThread_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

driver/Libraries/seekfree_peripheral/%.o: ./driver/Libraries/seekfree_peripheral/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


