BUILD=build
LIB=libnumcalcium
SRC_DIR=.
PLATFORM=f103c8

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c -I./$(LIB) $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections

all: $(LIB)/$(LIB).a | $(BUILD)
	@echo "======================="
	@echo "[$(LIB) built]"

example: $(LIB)/$(LIB).a
	+$(MAKE) -C example
example_sideload: example
	python3 util/sideload_serial.py

$(BUILD):
	mkdir $(BUILD)
$(LIB):
	mkdir $(LIB)

$(LIB)/$(LIB).a: $(BUILD)/vect.o $(BUILD)/crash.o $(BUILD)/sys.o $(BUILD)/loader.o | $(LIB)
	$(PRE)-ar rcs $@ $^

$(BUILD)/vect.o: $(LIB)/src/$(PLATFORM)_vector.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/sys.o: $(LIB)/src/$(PLATFORM)_stdlib.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/loader.o: $(LIB)/src/$(PLATFORM)_loader.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/crash.o: $(LIB)/src/$(PLATFORM)_crash.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD) libnumcalcium/libnumcalcium.a
	+$(MAKE) -C example clean