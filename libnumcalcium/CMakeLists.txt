cmake_minimum_required(VERSION 3.19)

project(libnumcalcium VERSION 0.0.1 DESCRIPTION "libnumcalcium CMake")

# enable_language(C ASM)
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
add_library(libnumcalcium STATIC
    src/f103c8_crash.c
    src/f103c8_loader.c
    src/f103c8_stdlib.c
    src/f103c8_vector.c
)

target_include_directories(libnumcalcium PRIVATE
    .
)

target_compile_options(libnumcalcium PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -fdata-sections
    -ffunction-sections
    -Wall
    $<$<CONFIG:Debug>:-Og>
)

# target_link_options(libnumcalcium PRIVATE
#     -Tld/f103c8_loader.ld
#     -mcpu=cortex-m3
#     -mthumb
#     -mfloat-abi=soft
#     -specs=nosys.specs
#     -Wl,-Map=${PROJECT_NAME}.map,--cref
#     -Wl,--gc-sections
# )
