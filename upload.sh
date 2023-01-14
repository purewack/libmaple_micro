#!/bin/bash
stm32flash -b 115200 -w build/maple.bin -v -g 0x0 /dev/tty.usbserial-1420
