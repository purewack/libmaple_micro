TARGET=cart
BUILD_DIR=build
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft 
CFLAGS= -c $(SYS) -std=gnu11 -Wall -o0
LDFLAGS = $(SYS) -nostdlib -T ../$(PLATFORM)_cart.ld -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

all: $(BUILD_DIR)/$(TARGET).bin 
	$(PRE)-objdump -D -h $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dias
	$(PRE)-nm $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).nm

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

main.o: main.c
	$(PRE)-gcc $(CFLAGS) -o $@ $^ 

$(BUILD_DIR)/$(TARGET).elf: main.o ../build/libnumcalcium.a
	$(PRE)-gcc $(LDFLAGS) $^ -o $@ 

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(PRE)-objcopy -v -O binary $^ $@ 

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.dias $(BUILD_DIR)/*.nm $(BUILD_DIR)/*.map