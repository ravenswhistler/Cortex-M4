#!bin/sh

gpp=arm-none-eabi-g++
gcc=arm-none-eabi-gcc
as=arm-none-eabi-as 
ld=arm-none-eabi-ld 
objdump=arm-none-eabi-objdump
nm=arm-none-eabi-nm
objcopy=arm-none-eabi-objcopy

SRC="./src/"
BLD="./build"
INC="-iquote ./include/ -iquote ./include/Core/ -iquote ./include/MCU/"

G_FLAGS="-O0 -std=gnu11 -nostdlib -ffreestanding -mgeneral-regs-only -nostartfiles"
COREFLAGS="-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mlittle-endian -march=armv7e-m+nofp -mtune=cortex-m4"
CPP_FLAGS="-fno-exceptions -fno-unwind-tables -no-rtti"
LDFLAGS="-gc-sections -print-memory-usage -static -Map=./build/mapper.map"

rm $BLD/*

$gcc $G_FLAGS $INC -v $COREFLAGS -c ./startup.c -o $BLD/startup.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/vtable.c -o $BLD/vtable.o
$gcc $G_FLAGS $INC $COREFLAGS -c $SRC/main.c -o $BLD/main.o

$ld $LDFLAGS -T./link.ld -o $BLD/CM4 $BLD/*.o

$objdump -D -S $BLD/CM4 > $BLD/CM4.list
$objcopy -O binary $BLD/CM4 $BLD/CM4.bin


