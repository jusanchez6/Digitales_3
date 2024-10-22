cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name (Replace C_Polling_Interrpupt with your own project's name)
project(C_Polling_Interrpupt)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(C_Polling_Interrpupt
    src/main.c
    src/detect_pwm.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(C_Polling_Interrpupt 
                    pico_stdlib
                    hardware_gpio
                    hardware_timer
                    hardware_pwm   
                    hardware_sync
                    )

# Enable usb output, disable uart output
pico_enable_stdio_usb(C_Polling_Interrpupt 1)
pico_enable_stdio_uart(C_Polling_Interrpupt 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(C_Polling_Interrpupt)