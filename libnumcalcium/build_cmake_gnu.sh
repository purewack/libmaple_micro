#!/bin/sh
# https://dev.to/younup/cmake-on-stm32-the-beginning-3766
WDIR=$(dirname "$0")
echo "Working in [$WDIR]"
cd $WDIR
cd ..
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../arm-cm3.cmake -DCMAKE_BUILD_TYPE=Debug ..
make