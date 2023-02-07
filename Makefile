BUILD=build
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c -I. $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections
LDFLAGS = --specs=nosys.specs $(SYS) -T ../src/$(PLATFORM)_loader.ld -Wl,-Map=$(D_BUILD_STAT)/$(EXE_FW).map,--emit-relocs

all: lib/libnumcalcium.a | $(BUILD)
	@echo "======================="
	@echo "[libnumcalcium built]"

$(BUILD):
	mkdir $(BUILD)
lib:
	mkdir lib

lib/libnumcalcium.a: $(BUILD)/vect.o $(BUILD)/crash.o $(BUILD)/sys.o $(BUILD)/loader.o | lib
	$(PRE)-ar rcs $@ $^

$(BUILD)/vect.o: src/$(PLATFORM)_vector.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/sys.o: src/$(PLATFORM)_stdlib.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/loader.o: src/$(PLATFORM)_loader.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/crash.o: src/crash.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD) lib/libnumcalcium.a