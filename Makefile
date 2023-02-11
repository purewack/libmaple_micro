BUILD=build
LIBNUM=libnumcalcium
LIBMAPLE=libnumcalcium/libmaple
PLATFORM=f103c8
BUILD_PATH=$(BUILD)
LIBMAPLE_PATH=$(LIBMAPLE)

PRE=arm-none-eabi
MACH=cortex-m3
SYS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft
CFLAGS= -c -I./$(LIBNUM) -I./$(LIBMAPLE)/include -I./$(LIBMAPLE)/stm32f1/include $(SYS) -std=gnu11 -Wall -o0 -fdata-sections -ffunction-sections

include $(LIBMAPLE)/rules.mk

all: $(LIBNUM)/$(LIBNUM).a | $(BUILD)
	@echo "======================="
	@echo "[libNumCalcium built]"

$(BUILD):
	mkdir $(BUILD)
$(LIBNUM):
	mkdir $(LIBNUM)

$(BUILD_PATH)/%.o: %.cpp
	$(SILENT_CXX) $(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBMAPLE_INCLUDES) -o $@ -c $< 

$(BUILD)/libmaple.a: $(TGT_BIN) | $(BUILD)
	$(PRE)-ar crv $(BUILD)/libmaple.a $(TGT_BIN)

$(LIBNUM)/$(LIBNUM).a: $(BUILD)/vect.o $(BUILD)/crash.o $(BUILD)/sys.o $(BUILD)/loader.o | $(LIBNUM)
	$(PRE)-ar rcs $@ $^

$(BUILD)/vect.o: $(LIBNUM)/src/$(PLATFORM)_vector.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/sys.o: $(LIBNUM)/src/$(PLATFORM)_stdlib.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/loader.o: $(LIBNUM)/src/$(PLATFORM)_loader.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

$(BUILD)/crash.o: $(LIBNUM)/src/$(PLATFORM)_crash.c | $(BUILD)
	$(PRE)-gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD) libnumcalcium/libnumcalcium.a
	+$(MAKE) -C example clean