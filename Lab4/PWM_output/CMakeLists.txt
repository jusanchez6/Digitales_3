# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
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
cmake_minimum_required(VERSION 3.13)


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
# Set the board type
set(PICO_BOARD pico CACHE STRING "Board type")

# Always include it
include(pico_sdk_import.cmake)

# Project's name 
project(PWM_OUTPUT C CXX)


# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(PWM_OUTPUT
    main.c

)

# Project's name and version
pico_set_program_name(PWM_OUTPUT "PWM_OUTPUT")
pico_set_program_version(PWM_OUTPUT "0.1")

# Enable usb output, disable uart output
pico_enable_stdio_usb(PWM_OUTPUT 1)
pico_enable_stdio_uart(PWM_OUTPUT 0)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(PWM_OUTPUT 
        pico_stdlib
        hardware_pwm)

# Add the standard library to the build
target_include_directories(PWM_OUTPUT PRIVATE 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/..
)


# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(PWM_OUTPUT)