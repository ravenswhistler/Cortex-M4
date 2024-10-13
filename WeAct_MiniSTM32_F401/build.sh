#!bin/sh

G_FLAGS="-O0 -std=gnu11 -nostdlib -ffreestanding -mgeneral-regs-only -nostartfiles"

COREFLAGS="-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mlittle-endian -march=armv7e-m+nofp -mtune=cortex-m4"

CPP_FLAGS="-fno-exceptions -fno-unwind-tables -no-rtti"

LDFLAGS="-gc-sections -print-memory-usage -static -Map=./build/mapper.map"

gpp=arm-none-eabi-g++
gcc=arm-none-eabi-gcc
as=arm-none-eabi-as 
ld=arm-none-eabi-ld 
objdump=arm-none-eabi-objdump

SRC="./src/"
BLD="./build"

rm $BLD/*

$gcc $G_FLAGS $COREFLAGS -c ./startup.c -o $BLD/startup.o
$gcc $G_FLAGS $COREFLAGS -c $SRC/vtable.c -o $BLD/vtable.o
$gcc $G_FLAGS $COREFLAGS -c $SRC/main.c -o $BLD/main.o

$ld $LDFLAGS -T./link.ld -o $BLD/CM4 $BLD/*.o

$objdump -D -S $BLD/CM4 > $BLD/CM4.list

