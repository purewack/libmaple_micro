cmake_minimum_required(VERSION 3.16)

project(example_firmware VERSION 0.0.1 DESCRIPTION "example_fw CMake")

# enable_language(C ASM)
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

set(EXECUTABLE firmware)

add_definitions(-DMCU_STM32F103C8)

add_subdirectory(libnumcalcium)
add_subdirectory(libnumcalcium/libmaple)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} PRIVATE 
    libnumcalcium
    libmaple
)

target_include_directories(${EXECUTABLE} PRIVATE
    libnumcalcium
    libnumcalcium/libmaple/include/
    libnumcalcium/libmaple/stm32f1/include/
)

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -fdata-sections
    -ffunction-sections
    -Wall
    $<$<CONFIG:Debug>:-Og>
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${CMAKE_SOURCE_DIR}/libnumcalcium/ld/f103c8_loader.ld
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -specs=nosys.specs
    -Wl,-Map=${EXECUTABLE}.map,--cref
    -Wl,--gc-sections
)

# Create hex file
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${TOOLCHAIN_PREFIX}objcopy -O binary ${EXECUTABLE} ${EXECUTABLE}.bin
    COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE}
    COMMAND ${TOOLCHAIN_PREFIX}nm ${EXECUTABLE} > ${CMAKE_BINARY_DIR}/${EXECUTABLE}.nm
    COMMAND ${TOOLCHAIN_PREFIX}objdump -D -h ${EXECUTABLE} > ${CMAKE_BINARY_DIR}/${EXECUTABLE}.dias
)