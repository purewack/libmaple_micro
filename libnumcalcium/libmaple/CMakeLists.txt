cmake_minimum_required(VERSION 3.16)

project(libmaple VERSION 0.0.13 DESCRIPTION "libmaple CMake")

# enable_language(C ASM)
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

add_definitions(-DMCU_STM32F103C8)

add_library(libmaple STATIC
    adc.c
    dac.c
    dma.c
    exti.c
    flash.c
    gpio.c
    i2c.c
    iwdg.c
    nvic.c
    pwr.c
    rcc.c
    spi.c
    systick.c
    timer.c
    usart.c
    usart_private.c
    util.c
    stm32f1/adc.c
    stm32f1/bkp.c
    stm32f1/dma.c
    stm32f1/exti.c
    stm32f1/fsmc.c
    stm32f1/gpio.c
    stm32f1/i2c.c
    stm32f1/rcc.c
    stm32f1/spi.c
    stm32f1/timer.c
    stm32f1/usart.c
)

target_include_directories(libmaple PRIVATE
    .
    include
    stm32f1/include
)

target_compile_options(libmaple PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -fdata-sections
    -ffunction-sections
    -Wall
    $<$<CONFIG:Debug>:-Og>
)

# target_link_options(libmaple PRIVATE
#     -Tld/f103c8_loader.ld
#     -mcpu=cortex-m3
#     -mthumb
#     -mfloat-abi=soft
#     -specs=nosys.specs
#     -Wl,-Map=${PROJECT_NAME}.map,--cref
#     -Wl,--gc-sections
# )
