PRE=arm-none-eabi
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -o0
LDFLAGS = -nostdlib -T f103c8.ld -Map=output.map

all: firmware.elf

vect.o: f103c8_vector.c
	$(PRE)-gcc $(CFLAGS) -o $@ $^

main.o: main.c
	$(PRE)-gcc $(CFLAGS) -o $@ $^

firmware.elf: main.o vect.o
	$(PRE)-ld $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf

dis:
	$(PRE)-objdump -D -h firmware.elf