cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Compiler options
set(STM32_MCU_FLAGS  "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard " )

#Linker options
set(STM32_LINKER_SCRIPT stm32h7r7xx_flash.ld)
set(STM32_LINKER_OPTION  )

# Include toolchain file
include("../gcc-arm-none-eabi.cmake")

# Set the project name
get_filename_component(PROJECT_ROOT_NAME ${CMAKE_SOURCE_DIR} NAME)
set(CMAKE_PROJECT_NAME ${PROJECT_ROOT_NAME})
project(${CMAKE_PROJECT_NAME})
add_executable(${CMAKE_PROJECT_NAME})

# Include mx-generated 
include("mx-generated.cmake")


# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED "true") 

# Set the path of lv_conf.h
set(LV_CONF_PATH ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_conf.h CACHE STRING "Path to lv_conf.h")

# Add the LVGL subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/../MiddlewareMy/lvgl lvgl)

# Add a USBX subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx usbx)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 
    # Add user defined symbols
)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/gt9xx
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lcd
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/key
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/buzzer

    ${CMAKE_SOURCE_DIR}/../MiddlewareMy
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lvgl/demos
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/gt9xx/gt9xx.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lcd/rgb_lcd_init.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/key/key_it.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/buzzer/passive_buzzer.c

    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_port_disp.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_port_indev.c

)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} 
    lvgl
    usbx 
    lvgl_demos
)


# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()









