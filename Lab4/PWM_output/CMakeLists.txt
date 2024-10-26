cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name 
project(PWM_OUTPUT C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(PWM_OUTPUT
    main.c

)

# Header folder
#include_directories(include)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(PWM_OUTPUT 
                    pico_stdlib
                    hardware_pwm
                    )

# Enable usb output, disable uart output
pico_enable_stdio_usb(PWM_OUTPUT 1)
pico_enable_stdio_uart(PWM_OUTPUT 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(PWM_OUTPUT)