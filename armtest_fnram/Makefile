TARGET=firmware
BUILD_DIR=build
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections
LDFLAGS = --specs=nosys.specs $(SYS) -T $(PLATFORM)_loader.ld -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--emit-relocs

all: $(BUILD_DIR)/firmware.bin 
	$(PRE)-objdump -D -h $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dias
	$(PRE)-nm $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).nm
	@echo "[Build complete] :"
	$(PRE)-size $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	mkdir $(BUILD_DIR)



$(BUILD_DIR)/libnumcalcium.a: $(BUILD_DIR)/vect.o $(BUILD_DIR)/crash.o $(BUILD_DIR)/loader.o $(BUILD_DIR)/sys.o
	$(PRE)-ar rcs $@ $^

$(BUILD_DIR)/vect.o: $(PLATFORM)_vector.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/sys.o: $(PLATFORM)_stdlib.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/crash.o: crash.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/loader.o: loader.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^



$(BUILD_DIR)/$(TARGET).elf: $(BUILD_DIR)/libnumcalcium.a
	$(PRE)-gcc $(LDFLAGS) $^ -o $@ 

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(PRE)-objcopy -v -O binary $^ $@ 
	
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.dias $(BUILD_DIR)/*.nm $(BUILD_DIR)/*.map $(BUILD_DIR)/*.a