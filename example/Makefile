EXE_FW=firmware
EXE_CART=cart
D_BUILD_FW=build_$(EXE_FW)
D_BUILD_CART=build_$(EXE_CART)
D_BUILD_STAT=build_debug
SRC_DIR=.
PLATFORM=f103c8
LIB=libnumcalcium

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c -I../$(LIB) $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections
LDFLAGS = --specs=nosys.specs $(SYS) -T ../$(LIB)/ld/$(PLATFORM)_loader.ld -Wl,-Map=$(D_BUILD_STAT)/$(EXE_FW).map
CFLAGS_CART= -c -I../$(LIB) $(SYS) -std=gnu11 -Wall -o0
LDFLAGS_CART = $(SYS) -T ../$(LIB)/ld/$(PLATFORM)_cart.ld -Wl,-Map=$(D_BUILD_STAT)/$(EXE_CART).map,--gc-sections

all: $(D_BUILD_FW)/firmware.bin $(D_BUILD_CART)/cart.bin | $(D_BUILD_STAT)
	$(PRE)-objdump -D -h $(D_BUILD_FW)/$(EXE_FW).elf > $(D_BUILD_STAT)/$(EXE_FW).dias
	$(PRE)-nm $(D_BUILD_FW)/$(EXE_FW).elf > $(D_BUILD_STAT)/$(EXE_FW).nm
	@echo "======================="
	@echo "[Build Stats] -> Firmware:"
	$(PRE)-size $(D_BUILD_FW)/$(EXE_FW).elf
	@echo "[Build Stats] -> Cart:"
	$(PRE)-size $(D_BUILD_CART)/$(EXE_CART).elf

$(D_BUILD_FW):
	mkdir $(D_BUILD_FW)
$(D_BUILD_CART):
	mkdir $(D_BUILD_CART)
$(D_BUILD_STAT):
	mkdir $(D_BUILD_STAT)


$(D_BUILD_FW)/main.o: main.c | $(D_BUILD_FW)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(D_BUILD_FW)/$(EXE_FW).elf: $(D_BUILD_FW)/main.o ../$(LIB)/libnumcalcium.a | $(D_BUILD_STAT)
	$(PRE)-gcc $(LDFLAGS) $^ -o $@ 

$(D_BUILD_FW)/$(EXE_FW).bin: $(D_BUILD_FW)/$(EXE_FW).elf
	$(PRE)-objcopy -v -O binary $^ $@ 



$(D_BUILD_CART)/main.o: cart/main.c | $(D_BUILD_CART) 
	$(PRE)-gcc $(CFLAGS_CART) -o $@ $^ 

$(D_BUILD_CART)/$(EXE_CART).elf: $(D_BUILD_CART)/main.o ../$(LIB)/libnumcalcium.a | $(D_BUILD_STAT)
	$(PRE)-gcc $(LDFLAGS_CART) $^ -o $@ 

$(D_BUILD_CART)/cart.bin: $(D_BUILD_CART)/$(EXE_CART).elf
	$(PRE)-objcopy -v -O binary $^ $@ 
	$(PRE)-objdump -D -h $(D_BUILD_CART)/$(EXE_CART).elf > $(D_BUILD_STAT)/$(EXE_CART).dias
	$(PRE)-nm $(D_BUILD_CART)/$(EXE_CART).elf > $(D_BUILD_STAT)/$(EXE_CART).nm
	
clean:
	rm -rf $(D_BUILD_FW) $(D_BUILD_CART)
