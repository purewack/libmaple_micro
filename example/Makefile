EXE_FW=firmware
EXE_CART=cart
D_BUILD_FW=build_$(EXE_FW)
D_BUILD_CART=build_$(EXE_CART)
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections
LDFLAGS = --specs=nosys.specs $(SYS) -T $(PLATFORM)_loader.ld -Wl,-Map=$(D_BUILD_FW)/$(EXE_FW).map,--emit-relocs
CFLAGS_CART= -c $(SYS) -std=gnu11 -Wall -o0
LDFLAGS_CART = $(SYS) -nostdlib -T $(PLATFORM)_cart.ld -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--gc-sections

all: $(D_BUILD_FW)/firmware.bin $(D_BUILD_CART)/cart.bin 
	$(PRE)-objdump -D -h $(D_BUILD_FW)/$(EXE_FW).elf > $(D_BUILD_FW)/$(EXE_FW).dias
	$(PRE)-nm $(D_BUILD_FW)/$(EXE_FW).elf > $(D_BUILD_FW)/$(EXE_FW).nm
	@echo "======================="
	@echo "[Build Stats] -> Firmware:"
	$(PRE)-size $(D_BUILD_FW)/$(EXE_FW).elf
	@echo "[Build Stats] -> Cart:"
	$(PRE)-size $(D_BUILD_CART)/$(EXE_CART).elf

$(D_BUILD_FW):
	mkdir $(D_BUILD_FW)
$(D_BUILD_CART):
	mkdir $(D_BUILD_CART)


$(D_BUILD_FW)/libnumcalcium.a: $(D_BUILD_FW)/vect.o $(D_BUILD_FW)/crash.o $(D_BUILD_FW)/loader.o $(D_BUILD_FW)/sys.o
	$(PRE)-ar rcs $@ $^


$(D_BUILD_FW)/vect.o: $(PLATFORM)_vector.c | $(D_BUILD_FW)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(D_BUILD_FW)/sys.o: $(PLATFORM)_stdlib.c | $(D_BUILD_FW)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(D_BUILD_FW)/crash.o: crash.c | $(D_BUILD_FW)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(D_BUILD_FW)/loader.o: loader.c | $(D_BUILD_FW)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(D_BUILD_FW)/$(EXE_FW).elf: $(D_BUILD_FW)/libnumcalcium.a
	$(PRE)-gcc $(LDFLAGS) $^ -o $@ 

$(D_BUILD_FW)/$(EXE_FW).bin: $(D_BUILD_FW)/$(EXE_FW).elf
	$(PRE)-objcopy -v -O binary $^ $@ 



$(D_BUILD_CART)/main.o: cart/main.c | $(D_BUILD_CART)
	$(PRE)-gcc $(CFLAGS_CART) -o $@ $^ 

$(D_BUILD_CART)/$(EXE_CART).elf: $(D_BUILD_CART)/main.o $(D_BUILD_FW)/libnumcalcium.a
	$(PRE)-gcc $(LDFLAGS_CART) $^ -o $@ 

$(D_BUILD_CART)/cart.bin: $(D_BUILD_CART)/$(EXE_CART).elf
	$(PRE)-objcopy -v -O binary $^ $@ 


clean:
	rm -rf $(D_BUILD_FW) $(D_BUILD_CART)