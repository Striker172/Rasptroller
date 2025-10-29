# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Controller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Controller Controller.c mfrc522.c)

pico_set_program_name(Controller "Controller")
pico_set_program_version(Controller "0.1")

# Modify the below lines to enable/disable output over UART/USB
# Enable UART stdio
pico_enable_stdio_uart(Controller 0)
# Enable USB stdio (CDC) so printf()/stdio goes over USB when connected.
# Set to 1 to enable. This requires linking the pico_stdio_usb library below.
pico_enable_stdio_usb(Controller 1)

# Add the standard library to the build
target_link_libraries(Controller
    pico_stdlib
    # USB stdio (CDC) helper - enables stdio over USB when pico_enable_stdio_usb was set.
    pico_stdio_usb
    )
target_sources( Controller PUBLIC
    ${CMAKE_CURRENT_LIST_DIR} Controller.c
    ${CMAKE_CURRENT_LIST_DIR} Button.c
    # ${CMAKE_CURRENT_LIST_DIR} usb.c
    # ${CMAKE_CURRENT_LIST_DIR} usb_descriptors.c
    )
# Add the standard include files to the build
target_include_directories(Controller PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Controller 
    hardware_spi
    hardware_gpio
    # tinyusb_device
    # tinyusb_board
    )

pico_add_extra_outputs(Controller)

