#!bin/sh

gpp=arm-none-eabi-g++
gcc=arm-none-eabi-gcc
as=arm-none-eabi-as 
ld=arm-none-eabi-ld 
objdump=arm-none-eabi-objdump
nm=arm-none-eabi-nm
objcopy=arm-none-eabi-objcopy
hd=hexdump

SRC="./src/"
BLD="./build"
INC="-iquote ./include/ -iquote ./include/Core/ -iquote ./include/MCU/"
#-mgeneral-regs-only 
G_FLAGS="-Wall -Wextra -O0 -std=gnu11 -nostdlib -ffreestanding -nostartfiles"
COREFLAGS="-mthumb -mabi=aapcs -mapcs-frame -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mlittle-endian -march=armv7e-m+nofp -mno-sched-prolog -mtune=cortex-m4 -mgeneral-regs-only"
CPP_FLAGS="-fno-exceptions -fno-unwind-tables -no-rtti"
LDFLAGS="-gc-sections -print-memory-usage -static -Map=./build/mapper.map"

rm $BLD/*

$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/vtable.c -o $BLD/vtable.o

$gcc $G_FLAGS $INC $COREFLAGS -c ./startup.c -o $BLD/startup.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/FLASH.c -o $BLD/FLASH.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/NVIC.c -o $BLD/NVIC.o

$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/sysclk.c -o $BLD/sysclk.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/interrupts.c -o $BLD/interrupts.o

#$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/Systick_blinky.c -o $BLD/Systick_blinky.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/TIMx_PWM.c -o $BLD/TIMx_PWM.o

$ld $LDFLAGS -T./link.ld -o $BLD/CM4 $BLD/*.o

$objdump -D -S $BLD/CM4 > $BLD/CM4.list
$objcopy -O binary $BLD/CM4 $BLD/CM4.bin
$hd -Cv $BLD/CM4.bin > $BLD/CM4.hex

