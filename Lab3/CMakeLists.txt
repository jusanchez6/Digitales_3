cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name 
project(LAB3 C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(LAB3
    src/main.c
    src/libs.c
)

# Header folder
include_directories(include)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(LAB3 
                    pico_stdlib
                    hardware_gpio
                    )

# Enable usb output, disable uart output
pico_enable_stdio_usb(LAB3 1)
pico_enable_stdio_uart(LAB3 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(LAB3)