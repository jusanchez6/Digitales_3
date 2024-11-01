cmake_minimum_required(VERSION 3.13)

# Project's name 
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Always include it
include(pico_sdk_import.cmake)

# Project's name 
project(C_Interrupt C CXX)


# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(C_Interrupt
    #src/test.c
    src/main.c
    src/detect_pwm.c
    src/7_seg.c
)

# Header folder
include_directories(include)

# Enable usb output, disable uart output
pico_enable_stdio_usb(C_Interrupt 1)
pico_enable_stdio_uart(C_Interrupt 0)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(C_Interrupt 
        pico_stdlib
        hardware_gpio
        hardware_timer
        hardware_pwm   
        hardware_sync)

target_include_directories(C_Interrupt PRIVATE 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/..
)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(C_Interrupt)