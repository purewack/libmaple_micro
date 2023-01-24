TARGET=firmware
BUILD_DIR=build
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -o0
LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft -nostdlib -T $(PLATFORM).ld -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

all: $(BUILD_DIR)/firmware.bin
	$(PRE)-objdump -D -h $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dias
	$(PRE)-nm $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).nm

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/vect.o: $(PLATFORM)_vector.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/crash.o: crash.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/$(TARGET).elf: $(BUILD_DIR)/main.o $(BUILD_DIR)/vect.o $(BUILD_DIR)/crash.o
	$(PRE)-gcc $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(PRE)-objcopy -v -O binary $^ $@ 
	
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.dias $(BUILD_DIR)/*.nm