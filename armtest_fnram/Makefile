PRE=arm-none-eabi
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -o0
LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft -nostdlib -T f103c8.ld -Wl,-Map=output.map

all: firmware.bin

vect.o: f103c8_vector.c
	$(PRE)-gcc $(CFLAGS) -o $@ $^

main.o: main.c
	$(PRE)-gcc $(CFLAGS) -o $@ $^

firmware.elf: main.o vect.o
	$(PRE)-gcc $(LDFLAGS) -o $@ $^

firmware.bin: firmware.elf
	$(PRE)-objcopy -v -O binary $^ $@ 

clean:
	rm -rf *.o *.elf *.bin

dis:
	$(PRE)-objdump -D -h firmware.elf
